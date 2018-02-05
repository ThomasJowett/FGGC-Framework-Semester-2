#include "ParticleModel.h"
ParticleModel::ParticleModel(float mass, Transform * transform) : _mass(mass), _transform(transform)
{

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
	_acceleration = _netForce / _mass;

	_velocity = _velocity + (_acceleration * deltaTime);

	if (_velocity == Vector{ 0.0f, 0.0f, 0.0f })
		_isAtRest = true;
	else
	{
		_transform->SetPosition(_transform->GetPosition() + _velocity);
		_isAtRest = false;
	}

	_netForce = Vector{ 0.0f,0.0f,0.0f };
}

void ParticleModel::MoveForward(float speed, float deltaTime)
{
	Vector position = _transform->GetPosition();
	position.z = position.z + (-0.1f * deltaTime);
	_transform->SetPosition(position);
}
