#pragma once
#include <list>

class GameObjectPool
{
public:
	GameObjectPool(GameObject initialiser) : _initialiser(initialiser){}

	GameObject* GetGameObject()
	{
		if (_gameObjects.empty())
		{
			Transform* transform = new Transform((_initialiser.GetTransform()->GetPosition()), _initialiser.GetTransform()->GetRotation(), _initialiser.GetTransform()->GetScale());
			ParticleModel* particleModel = new ParticleModel(_initialiser.GetPhysicsComponent()->GetMass(), _initialiser.GetPhysicsComponent()->GetVelocity(), transform);
			return new GameObject(_initialiser.GetType(),_initialiser.GetAppearance(),transform,particleModel,_initialiser.GetCollider());
		}
		else
		{
			GameObject* newObject = _gameObjects.front();
			_gameObjects.pop_front();
			return newObject;
		}
	}

	void ReturnGameObject(GameObject* object)
	{
		_gameObjects.push_back(object);
	}

	void CleanUp()
	{
		for (auto resource : _gameObjects)
			delete resource;

		_gameObjects.empty();
	}

	void ReleaseGameObject(GameObject* object)
	{
		_gameObjects.remove(object);
		delete object;
	}

	void PreloadGameObjects(int numberToLoad)
	{
		for (int i = 0; i < numberToLoad; i++)
		{
			ReturnGameObject(GetGameObject());
		}
	}

private:
	std::list<GameObject*>_gameObjects;
	GameObject _initialiser;
};
