#pragma once
#include "Vector.h"
#include "Transform.h"
#include "Collision.h"

class ParticleModel
{
public:
	ParticleModel(float mass, Vector velocity, float boundingRadius, Transform * transform);
	~ParticleModel();

	void AddForce(Vector force);

	void Update(float deltaTime);

	bool GetSimulatePhysics() const { return _simulatePhysics; }
	void SetSimulatePhysics(bool simulate) { _simulatePhysics = simulate; }

	float GetMass() const { return _mass; }
	void SetMass(float mass) { _mass = mass; }

	Vector GetVelocity() const { return _velocity; }

	Sphere* GetBoundingSphere() const { return _boundingSphere; }

private:
	Transform * _transform;
	bool _isAtRest;
	bool _laminar;
	Vector _velocity;
	Vector _netForce;
	float _mass;
	bool _simulatePhysics;
	float _dragCoefficient;
	float _fluidDensity;
	float _objectArea;

	Sphere* _boundingSphere;

	Vector DragForce();
	Vector DragLaminarFlow();
	Vector DragTurbulentFlow();
};

