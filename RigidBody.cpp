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
	//convert to coordinates relative to center of mass
	Vector3D pt = _transform->GetPosition() - point;
	Vector3D torque = Vector3D::Cross(force, pt);
	//AddForce(force - torque);

	_netTorque += torque;
}

void RigidBody::Update(float deltaTime)
{
	ParticleModel::Update(deltaTime);

	float inertia = GetInertia(_angularVelocity.GetNormalized());
	Vector3D angularAcceleration;

	if (inertia)
		angularAcceleration = _netTorque / inertia;
	else
		angularAcceleration = { 0.0f,0.0f,0.0f };

	//add angular acceleration to angular velocity
	_angularVelocity += angularAcceleration * deltaTime;

	Quaternion rotation = _transform->GetRotation();

	rotation.addScaledVector(_angularVelocity, deltaTime);

	rotation.Normalize();

	_transform->SetRotation(rotation);

	_netTorque = { 0.0f, 0.0f, 0.0f };
}

float RigidBody::GetInertia(Vector3D axis)
{
	Vector3D localAxis = axis;
	localAxis.x /= (GetPhysicsMaterial().inertiaTensor._11) 
		+ (GetPhysicsMaterial().inertiaTensor._12) 
		+ (GetPhysicsMaterial().inertiaTensor._13);

	localAxis.y /= (GetPhysicsMaterial().inertiaTensor._21)
		+ (GetPhysicsMaterial().inertiaTensor._22)
		+ (GetPhysicsMaterial().inertiaTensor._23);

	localAxis.z /= (GetPhysicsMaterial().inertiaTensor._31)
		+ (GetPhysicsMaterial().inertiaTensor._32)
		+ (GetPhysicsMaterial().inertiaTensor._33);
	return localAxis.GetMagnitude();
}
