#pragma once
#include "ParticleModel.h"
class RigidBody :public ParticleModel
{
public:
	RigidBody(float mass, Vector3D velocity, Transform * transform, Vector3D rotationAxis, float rotationRate);
	~RigidBody();

	void Update(float deltaTime)override;
private:
	Vector3D	_rotationAxis;
	float	_rotationRate;
};

