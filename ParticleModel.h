#pragma once
#include "Vector.h"
#include "Transform.h"
#include "Collider.h"

class ParticleModel
{
public:
	ParticleModel(float mass, Vector3D velocity, Transform * transform);
	~ParticleModel();

	void AddForce(Vector3D force);

	virtual void Update(float deltaTime);

	bool GetSimulatePhysics() const { return _simulatePhysics; }
	void SetSimulatePhysics(bool simulate) { _simulatePhysics = simulate; }

	float GetMass() const { return _mass; }
	void SetMass(float mass) { _mass = mass; }

	Vector3D GetVelocity() const { return _velocity; }
	void SetVelocity(Vector3D velocity) { _velocity = velocity; }

	bool GetIsLaminar()const { return _isLaminar; }
	void SetIsLaminar(bool laminar) { _isLaminar = laminar; }

protected:
	Transform * _transform;

private:
	bool _isAtRest;
	bool _isLaminar;
	Vector3D _velocity;
	Vector3D _netForce;
	float _mass;
	bool _simulatePhysics;
	float _dragCoefficient;
	float _fluidDensity;
	float _objectArea;

	Vector3D GravityForce();
	Vector3D DragForce();
	Vector3D DragLaminarFlow();
	Vector3D DragTurbulentFlow();
};

