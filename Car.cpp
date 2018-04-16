#include "Car.h"

Car::Car(string type, Appearance * appearance, Transform * transform, ParticleModel * particleModel, Collider* collider)
	:GameObject(type, appearance, transform, particleModel, collider)
{
	_forward = { 0.0f, 0.0f, 1.0f };
	_maxSpeed = 1000.0f;
}

Car::~Car()
{
}

void Car::MoveRight(float deltaTime, float scale)
{

}

void Car::MoveForward(float deltaTime, float scale)
{
	_physicsComponent->AddForce((_transform->GetRotation() * _forward) * scale  * _maxSpeed);
}

void Car::Yaw(float deltaTime, float scale)
{
}

void Car::Pitch(float deltaTime, float scale)
{
}

void Car::Roll(float deltaTime, float scale)
{
}
