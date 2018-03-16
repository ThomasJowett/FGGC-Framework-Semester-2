#pragma once
#include <list>

class GameObjectPool
{
public:
	GameObject* GetGameObject(GameObject* object)
	{
		if (_gameObjects.empty())
		{
			return new GameObject(*object);
		}
		else
		{
			GameObject* newObject = _gameObjects.front();
			newObject = object;
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

	void RelesaseGameObject(GameObject* object)
	{
		_gameObjects.remove(object);
		delete object;
	}

private:
	std::list<GameObject*>_gameObjects;
};