#include "ParticleModel.h"
ParticleModel::ParticleModel(float mass, Vector3D velocity, Transform * transform) : _mass(mass), _transform(transform), _velocity(velocity)
{
	if (mass <= 0.0f)
		_simulatePhysics = false;

	_dragCoefficient = 1.0f;
	_fluidDensity = 1.225f;
	_objectArea = 1.0f;
}

ParticleModel::~ParticleModel()
{
}

void ParticleModel::AddForce(Vector3D force)
{
	_netForce += force;
}

void ParticleModel::Update(float deltaTime)
{
	if (_simulatePhysics)
	{
		AddForce(GravityForce());
		AddForce(DragForce());

		Vector3D acceleration = _netForce / _mass;
		if (!_isAtRest) 
		{
			Vector3D position = _transform->GetPosition();
			position += (_velocity*deltaTime) + (acceleration*(deltaTime*deltaTime)) / 2;

			_transform->SetPosition(position);
		}
		_velocity += acceleration * deltaTime;

		if (_velocity.GetSqrMagnitude() < 0.01f)
		{
			_velocity = { 0.0f, 0.0f, 0.0f };
			_isAtRest = true;
		}
		else
		{
			_isAtRest = false;
		}
		_netForce = Vector3D{ 0.0f,0.0f,0.0f };
	}
}

Vector3D ParticleModel::GravityForce()
{
	return Vector3D({ 0.0f, -10.0f, 0.0f }) * _mass;
}

Vector3D ParticleModel::DragForce()
{
	_isLaminar = true;

	if (_isLaminar)
		return DragLaminarFlow();
	else
		return DragTurbulentFlow();
}

Vector3D ParticleModel::DragLaminarFlow()
{
	return _velocity * -_dragCoefficient;
}

Vector3D ParticleModel::DragTurbulentFlow()
{
	float velocitySqrMagnitude = _velocity.GetSqrMagnitude();
	Vector3D unitVelocity = _velocity.GetNormalized();
	float dragMagnitude = 0.5*_fluidDensity*_dragCoefficient*_objectArea*velocitySqrMagnitude;

	return unitVelocity * -dragMagnitude;
}

