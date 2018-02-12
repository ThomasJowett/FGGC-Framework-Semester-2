#include "ParticleModel.h"
ParticleModel::ParticleModel(float mass, Vector velocity, Transform * transform) : _mass(mass), _transform(transform), _velocity(velocity)
{
	if (mass <= 0)
		_simulatePhysics = false;

	_dragCoefficient = 1.05f;
	_fluidDensity = 1.225f;
	_objectArea = 1.0f;
}

ParticleModel::~ParticleModel()
{
}

void ParticleModel::AddForce(Vector force)
{
	_netForce += force;
}

void ParticleModel::Update(float deltaTime)
{
	if (_simulatePhysics)
	{
		AddForce(DragForce());

		Vector acceleration = _netForce / _mass;

		_velocity = _velocity + (acceleration * deltaTime);

		if (_velocity.GetSqrMagnitude() == 0.0f)
			_isAtRest = true;
		else
		{
			_transform->SetPosition(_transform->GetPosition() + _velocity);
			_isAtRest = false;
		}

		_netForce = Vector{ 0.0f,0.0f,0.0f };
	}
}

void ParticleModel::MoveForward(float speed, float deltaTime)
{
	Vector position = _transform->GetPosition();
	position.z = position.z + (-0.1f * deltaTime);
	_transform->SetPosition(position);
}

Vector ParticleModel::DragForce()
{
	_laminar = true;

	if (_laminar)
		return DragLaminarFlow();
	else
		return DragTurbulentFlow();
}

Vector ParticleModel::DragLaminarFlow()
{
	return _velocity * -_dragCoefficient;
}

Vector ParticleModel::DragTurbulentFlow()
{
	float velocitySqrMagnitude = _velocity.GetSqrMagnitude();
	Vector unitVelocity = _velocity.GetNormalized();
	float dragMagnitude = 0.5*_fluidDensity*_dragCoefficient*_objectArea*velocitySqrMagnitude;

	return unitVelocity * -dragMagnitude;
}

