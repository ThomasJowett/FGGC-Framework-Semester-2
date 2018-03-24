#pragma once
#include "GameObject.h"
#include "RigidBody.h"
class GameObjectRigidBody :	public GameObject
{
public:
	GameObjectRigidBody(string type, Appearance * appearance, Transform * transform, RigidBody * rigidBody);
	~GameObjectRigidBody();

	void Update(float deltaTime) override;
	ParticleModel* GetPhysicsComponent() const { return _rigidBody; }
private:
	RigidBody* _rigidBody;
};

