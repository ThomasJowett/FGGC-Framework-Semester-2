#pragma once
#include "Vector.h"
class ParticleModel
{
public:
	ParticleModel(float mass) : _mass(mass) {};
	~ParticleModel();

	void AddForce();

private:
	bool IsAtRest;
	Vector _velocity;
	Vector _netForce;
	float _mass;
};

