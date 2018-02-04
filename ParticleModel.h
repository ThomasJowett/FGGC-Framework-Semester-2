#pragma once
#include "Vector.h"
#include "Transform.h"

class ParticleModel
{
public:
	ParticleModel(float mass, Transform * transform) : _mass(mass), _transform(transform) {};
	~ParticleModel();

	void AddForce();

	void Update(float deltaTime);

	void MoveForward(float speed, float deltaTime);

private:
	Transform * _transform;
	bool IsAtRest;
	Vector _velocity;
	Vector _netForce;
	float _mass;
};

