#include "GameObjectRigidBody.h"



GameObjectRigidBody::GameObjectRigidBody(string type, Appearance * appearance, Transform * transform, RigidBody * rigidBody)
	: GameObject(type, appearance, transform, nullptr), _rigidBody(rigidBody)
{
}


GameObjectRigidBody::~GameObjectRigidBody()
{
}

void GameObjectRigidBody::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if(_rigidBody != nullptr)
		_rigidBody->Update(deltaTime);
}
