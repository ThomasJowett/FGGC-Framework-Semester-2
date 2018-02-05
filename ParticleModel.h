#pragma once
#include "Vector.h"
#include "Transform.h"

class ParticleModel
{
public:
	ParticleModel(float mass, Transform * transform);
	~ParticleModel();

	void AddForce(Vector force);

	void Update(float deltaTime);

	void MoveForward(float speed, float deltaTime);

private:
	Transform * _transform;
	bool _isAtRest;
	Vector _velocity;
	Vector _acceleration;
	Vector _netForce;
	float _mass;
};

