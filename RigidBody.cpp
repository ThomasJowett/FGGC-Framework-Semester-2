#include "RigidBody.h"

RigidBody::RigidBody(float mass, Vector3D velocity, Transform * transform, Vector3D rotationAxis, float rotationRate)
	:ParticleModel(mass, velocity, transform)
{
	if (rotationAxis.GetSqrMagnitude() != 0.0f)
	{
		_angularVelocity = rotationAxis.GetNormalized() * rotationRate;
	}
	else
	{
		_angularVelocity = Vector3D{ 0.0f,1.0f,0.0f } * rotationRate;
	}

	_angularDrag = 1.0f;
}


RigidBody::~RigidBody()
{
}

void RigidBody::AddPointForce(Vector3D force, Vector3D point)
{
	Vector3D torque = Vector3D::Cross(force, point);
	//AddForce(force);

	_netTorque += torque;
}

void RigidBody::AddPointForceWorld(Vector3D force, Vector3D point)
{
	//convert from world to local
	Vector3D pt = _transform->GetPosition() - point;
	AddPointForce(force, pt);
}

void RigidBody::AddTorque(Vector3D torque)
{
	_netTorque += torque;
}

void RigidBody::Update(float deltaTime)
{
	ParticleModel::Update(deltaTime);

	AddTorque(_angularVelocity * -_angularDrag);

	float inertia = GetInertia(_netTorque.GetNormalized());
	Vector3D angularAcceleration;

	if (inertia)
		angularAcceleration = _netTorque / inertia;
	else
		angularAcceleration = { 0.0f,0.0f,0.0f };

	//add angular acceleration to angular velocity
	_angularVelocity += angularAcceleration * deltaTime;

	Quaternion rotation = _transform->GetRotation();

	rotation.AddScaledVector(_angularVelocity, deltaTime);

	rotation.Normalize();

	_transform->SetRotation(rotation);

	_netTorque = { 0.0f, 0.0f, 0.0f };
}

float RigidBody::GetInertia(Vector3D axis)
{
	Vector3D localAxis = axis;
	PhysicsMaterial material = GetPhysicsMaterial();
	localAxis.x /= (material.inertiaTensor._11)
		+ (material.inertiaTensor._12)
		+ (material.inertiaTensor._13);

	localAxis.y /= (material.inertiaTensor._21)
		+ (material.inertiaTensor._22)
		+ (material.inertiaTensor._23);

	localAxis.z /= (material.inertiaTensor._31)
		+ (material.inertiaTensor._32)
		+ (material.inertiaTensor._33);
	return localAxis.GetMagnitude();
}
