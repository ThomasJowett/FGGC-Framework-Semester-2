#pragma once
#include "ParticleModel.h"
class RigidBody :public ParticleModel
{
public:
	RigidBody(float mass, Vector velocity, float boundingRadius, Transform * transform, Vector rotationAxis, float rotationRate);
	~RigidBody();

	void Update(float deltaTime)override;
private:
	Vector	_rotationAxis;
	float	_rotationRate;
};

