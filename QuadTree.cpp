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

	MAXOBJECTS = 10;
	MAXLEVELS = 5;
}

QuadTree::QuadTree(AABB* boundary, int level) : _boundary(boundary), _level(level)
{	
	_nodes[0] = nullptr;
	_nodes[1] = nullptr;
	_nodes[2] = nullptr;
	_nodes[3] = nullptr;

	_gameObjects = std::vector<GameObject*>();

	MAXOBJECTS = 10;
	MAXLEVELS = 5;
}

QuadTree::~QuadTree()
{
	for (auto node : _nodes)
		if (node != nullptr)
		{
			delete node;
		}
}

bool QuadTree::Insert(GameObject* gameObject)
{
	if (_nodes[0] != nullptr) 
	{
		int index = GetIndex(gameObject);

		if (index != -1) 
		{
			_nodes[index]->Insert(gameObject);
			return true;
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
				_nodes[index]->Insert(_gameObjects[i]);
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
	_nodes[0] = new QuadTree(new AABB(transform, halfWidth, _boundary->GetHeight(), halfDepth), _level + 1);

	//north East
	transform = new Transform();
	transform->SetPosition(Vector3D(_boundary->GetCentre().x + halfWidth, _boundary->GetCentre().y, _boundary->GetCentre().z + halfDepth));
	_nodes[1] = new QuadTree(new AABB(transform, halfWidth, _boundary->GetHeight(), halfDepth), _level + 1);

	//South West
	transform = new Transform();
	transform->SetPosition(Vector3D(_boundary->GetCentre().x + halfWidth, _boundary->GetCentre().y, _boundary->GetCentre().z - halfDepth));
	_nodes[2] = new QuadTree(new AABB(transform, halfWidth, _boundary->GetHeight(), halfDepth), _level + 1);

	//South East
	transform = new Transform();
	transform->SetPosition(Vector3D(_boundary->GetCentre().x - halfWidth, _boundary->GetCentre().y, _boundary->GetCentre().z - halfDepth));
	_nodes[3] = new QuadTree(new AABB(transform, halfWidth, _boundary->GetHeight(), halfDepth), _level + 1);
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
	bool northHalf = (gameobject->GetCollider()->TestZAxisValue(_boundary->GetCentre().z,true) && 
		gameobject->GetCollider()->TestZAxisValue(_boundary->GetZMax(), false));
	bool southHalf = (gameobject->GetCollider()->TestZAxisValue(_boundary->GetCentre().z, false) &&
		gameobject->GetCollider()->TestZAxisValue(_boundary->GetZMin(), true));

	if (gameobject->GetCollider()->TestXAxisValue(_boundary->GetCentre().x, true))
	{
		if (northHalf)
			index = 1;
		else if (southHalf)
			index = 2;
	}
	else if (gameobject->GetCollider()->TestXAxisValue(_boundary->GetCentre().x, false))
	{
		if (northHalf)
			index = 0;
		else if(southHalf)
			index = 3;
	}

	return index;
}

std::vector<GameObject*> QuadTree::Retrieve(GameObject * gameobject)
{
	int index = GetIndex(gameobject);
	std::vector<GameObject*> returnObjects;
	if (index != -1 && _nodes[0] != nullptr)
	{
		_nodes[index]->Retrieve(gameobject);
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

