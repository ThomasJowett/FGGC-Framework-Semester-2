#include "ParticleModel.h"
ParticleModel::ParticleModel(float mass, Vector velocity, float boundingRadius, Transform * transform) : _mass(mass), _transform(transform), _velocity(velocity)
{
	if (mass <= 0.0f)
		_simulatePhysics = false;

	_dragCoefficient = 1.0f;
	_fluidDensity = 1.225f;
	_objectArea = 1.0f;

	_boundingSphere = new Sphere(boundingRadius, _transform);
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
		AddForce(GravityForce());
		AddForce(DragForce());

		Vector acceleration = _netForce / _mass;

		if (_velocity.GetSqrMagnitude() < 0.0f)
			_isAtRest = true;
		else
		{
			Vector position = _transform->GetPosition();
			position.x += _velocity.x * deltaTime + 0.5f * acceleration.x * deltaTime * deltaTime;
			position.y += _velocity.y * deltaTime + 0.5f * acceleration.y * deltaTime * deltaTime;
			position.z += _velocity.z * deltaTime + 0.5f * acceleration.z * deltaTime * deltaTime;

			//_transform->SetPosition(_transform->GetPosition() + _velocity * deltaTime + 0.5f * acceleration * deltaTime * deltaTime);

			_transform->SetPosition(position);
			_isAtRest = false;
		}

		_velocity = _velocity + (acceleration * deltaTime);

		_netForce = Vector{ 0.0f,0.0f,0.0f };
	}
}

Vector ParticleModel::GravityForce()
{
	return Vector({ 0.0f, -10.0f, 0.0f }) * _mass;
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

