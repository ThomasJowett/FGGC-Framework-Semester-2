#include "Car.h"

Car::Car(string type, Appearance * appearance, Transform * transform, RigidBody * physicsComponent, Collider* collider)
	:GameObject(type, appearance, transform, physicsComponent, collider)
{
	_forward = { 0.0f, 0.0f, 1.0f };
	_maxSpeed = 3000.0f;
	_rotationSpeed = 0.1f;
	_rigidBody = physicsComponent;
}

Car::~Car()
{
}

void Car::MoveRight(float deltaTime, float scale)
{

}

void Car::MoveForward(float deltaTime, float scale)
{
	_forward = _transform->GetRotation().Inverse().RotateVectorByQuaternion( Vector3D{ 0.0f, 0.0f, 1.0f });
	_rigidBody->AddForce(_forward * scale* _maxSpeed);
}

void Car::Yaw(float deltaTime, float scale)
{
	if (_rigidBody->GetVelocity().GetSqrMagnitude() > 1.0f)
	{
		_rigidBody->AddPointForce({ 0.0f, 0.0f, scale*_rotationSpeed }, { 20.0f, 0.0f, 0.0f });
	}
}

void Car::Pitch(float deltaTime, float scale)
{
}

void Car::Roll(float deltaTime, float scale)
{
}
