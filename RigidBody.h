#pragma once
#include "ParticleModel.h"
class RigidBody :public ParticleModel
{
public:
	RigidBody(float mass, Vector3D velocity, Transform * transform, Vector3D rotationAxis, float rotationRate);
	~RigidBody();

	void AddPointForce(Vector3D force, Vector3D point);
	void AddPointForceWorld(Vector3D force, Vector3D point);

	void AddTorque(Vector3D torque);

	void Update(float deltaTime)override;
private:
	float _angularDrag;
	Vector3D _angularVelocity;

	Vector3D _netTorque;

	float GetInertia(Vector3D axis);
};

