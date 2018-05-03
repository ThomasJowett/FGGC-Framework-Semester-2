#include "QuadTree.h"


QuadTree::QuadTree()
{
	_level = 0;
	Transform* transform = new Transform();
	_boundary = new AABB(transform, 1000.0f, 1000.0f, 1000.0f);

	_nodes[0] = nullptr;
	_nodes[1] = nullptr;
	_nodes[2] = nullptr;
	_nodes[3] = nullptr;

	_gameObjects = std::vector<GameObject*>();
	_parentIndex = -1;

	MAXOBJECTS = 1;
	MAXLEVELS = 10;
}

QuadTree::QuadTree(AABB* boundary, int level, int parentIndex) : _boundary(boundary), _level(level), _parentIndex(parentIndex)
{	
	_nodes[0] = nullptr;
	_nodes[1] = nullptr;
	_nodes[2] = nullptr;
	_nodes[3] = nullptr;

	_gameObjects = std::vector<GameObject*>();

	MAXOBJECTS = 5;
	MAXLEVELS = 20;
}

QuadTree::~QuadTree()
{
	Clear();
}

void QuadTree::Insert(GameObject* gameObject)
{
	if (_nodes[0] != nullptr) 
	{
		int index = GetIndex(gameObject);

		if (index != -1) 
		{
			_nodes[index]->Insert(gameObject);
			return;
		}
	}
	_gameObjects.push_back(gameObject);

	if (_gameObjects.size() > MAXOBJECTS && _level < MAXLEVELS)
	{
		if (_nodes[0] == nullptr)
		{
			Subdivide();
		}

		int i = 0;
		while (i < _gameObjects.size())
		{
			int index = GetIndex(_gameObjects.at(i));
			if (index != -1)
			{
				_nodes[index]->Insert(_gameObjects.at(i));
				_gameObjects.erase(_gameObjects.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}

void QuadTree::Subdivide()
{
	float halfWidth = _boundary->GetWidth()/2;
	float halfDepth = _boundary->GetDepth()/2;
	
	//north West
	Transform * transform = new Transform(Vector3D(_boundary->GetCentre().x - halfWidth, _boundary->GetCentre().y, _boundary->GetCentre().z + halfDepth), {}, { 1.0f,1.0f,1.0f });
	_nodes[0] = new QuadTree(new AABB(transform, halfWidth, _boundary->GetHeight(), halfDepth), _level + 1, 0);

	//north East
	transform = new Transform();
	transform->SetPosition(Vector3D(_boundary->GetCentre().x + halfWidth, _boundary->GetCentre().y, _boundary->GetCentre().z + halfDepth));
	_nodes[1] = new QuadTree(new AABB(transform, halfWidth, _boundary->GetHeight(), halfDepth), _level + 1, 1);

	//South West
	transform = new Transform();
	transform->SetPosition(Vector3D(_boundary->GetCentre().x - halfWidth, _boundary->GetCentre().y, _boundary->GetCentre().z - halfDepth));
	_nodes[2] = new QuadTree(new AABB(transform, halfWidth, _boundary->GetHeight(), halfDepth), _level + 1, 2);

	//South East
	transform = new Transform();
	transform->SetPosition(Vector3D(_boundary->GetCentre().x + halfWidth, _boundary->GetCentre().y, _boundary->GetCentre().z - halfDepth));
	_nodes[3] = new QuadTree(new AABB(transform, halfWidth, _boundary->GetHeight(), halfDepth), _level + 1, 3);
}

std::vector<GameObject*> QuadTree::QueryRange(AABB* range)
{
	std::vector<GameObject*>inRangeOf = std::vector<GameObject*>();
	float penetrationDepth;
	Vector3D normal;

	//check if the range box is overlapping with this quad
	if (!_boundary->IntersectsCollider(range, normal, penetrationDepth))
	{
		return inRangeOf; //if no then it can't be overlapping with any objects in it
	}

	for (int i = 0; i < _gameObjects.size(); i++)
	{
		if (range->ContainsPoint(_gameObjects[i]->GetTransform()->GetPosition()))
		{
			inRangeOf.push_back(_gameObjects.at(i));
		}
	}

	if (_nodes[0] == nullptr)
	{
		return inRangeOf;
	}

	std::vector<GameObject*> temp;

	for (auto node : _nodes)
	{
		node->QueryRange(range);
		inRangeOf.insert(inRangeOf.end(), temp.begin(), temp.end());
	}

	return inRangeOf;
}

int QuadTree::GetIndex(GameObject * gameobject)
{
	int index = -1;
	Collider* collider = gameobject->GetCollider();
	bool northHalf = (collider->TestZAxisValue(_boundary->GetCentre().z,true) &&
		collider->TestZAxisValue(_boundary->GetZMax(), false));
	bool southHalf = (collider->TestZAxisValue(_boundary->GetCentre().z, false) &&
		collider->TestZAxisValue(_boundary->GetZMin(), true));

	if (collider->TestXAxisValue(_boundary->GetCentre().x, true) && collider->TestXAxisValue(_boundary->GetXMax(),false))
	{
		if (northHalf)
			index = 1;//North East
		else if (southHalf)
			index = 3; //South East
	}
	else if (collider->TestXAxisValue(_boundary->GetCentre().x, false) && collider->TestXAxisValue(_boundary->GetXMin(), true))
	{
		if (northHalf)
			index = 0;//North West
		else if(southHalf)
			index = 2;//South West
	}

	return index;
}

std::vector<GameObject*> QuadTree::Retrieve(std::vector<GameObject*>& returnObjects, GameObject * gameobject)
{
	int index = GetIndex(gameobject);
	if (index != -1 && _nodes[0] != nullptr)
	{
		_nodes[index]->Retrieve(returnObjects, gameobject);
	}

	for (GameObject* gameObject : _gameObjects)
	{
		returnObjects.push_back(gameObject);
	}
	
	return returnObjects;
}

void QuadTree::Clear()
{
	_gameObjects.clear();

	if (_nodes[0] != nullptr)
	{
		_nodes[0]->Clear();
		_nodes[1]->Clear();
		_nodes[2]->Clear();
		_nodes[3]->Clear();
	}

	_nodes[0] = nullptr;
	_nodes[1] = nullptr;
	_nodes[2] = nullptr;
	_nodes[3] = nullptr;
}

