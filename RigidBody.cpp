#include "RigidBody.h"



RigidBody::RigidBody(float mass, Vector3D velocity, Transform * transform, Vector3D rotationAxis, float rotationRate)
	:ParticleModel(mass, velocity, transform), _rotationRate(rotationRate)
{
	if (rotationAxis.GetSqrMagnitude() != 0.0f)
	{
		_rotationAxis = rotationAxis.GetNormalized();
	}
	else
	{
		_rotationAxis = { 0.0f,1.0f,0.0f };
	}
}


RigidBody::~RigidBody()
{
}

void RigidBody::Update(float deltaTime)
{
	ParticleModel::Update(deltaTime);

	Vector3D angularAcceleration;
	//some calculation of angular acceleration

	Vector3D angularVelocity = _rotationAxis * _rotationRate;

	//add angular acceleration to angular velocity

	Quaternion rotation = _transform->GetRotation();

	rotation.addScaledVector(angularVelocity, deltaTime);

	_transform->SetRotation(rotation);
}
