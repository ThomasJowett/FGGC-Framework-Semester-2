#include "RigidBody.h"



RigidBody::RigidBody(float mass, Vector velocity, float boundingRadius, Transform * transform, Vector rotationAxis, float rotationRate)
	:ParticleModel(mass, velocity, boundingRadius, transform), _rotationAxis(rotationAxis), _rotationRate(rotationRate)
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::Update(float deltaTime)
{
	ParticleModel::Update(deltaTime);

	Vector angularAcceleration;
	//some calculation of angular acceleration

	Vector angularVelocity = _rotationAxis * _rotationRate;

	//add angular acceleration to angular velocity

	Quaternion rotation = _transform->GetRotation();

	rotation.addScaledVector(angularVelocity, deltaTime);

	_transform->SetRotation(rotation);
}
