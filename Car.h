#ifndef _CAR_H
#define _CAR_H

#include "GameObject.h"
#include "iInput.h"

class Car: public GameObject , public iInput
{
public:
	Car(string type, Appearance * appearance, Transform * transform, ParticleModel * particleModel, Collider* collider);
	~Car();
	virtual void MoveRight(float deltaTime, float scale);
	virtual void MoveForward(float deltaTime, float scale);

	virtual void Yaw(float deltaTime, float scale);
	virtual void Pitch(float deltaTime, float scale);
	virtual void Roll(float deltaTime, float scale);
private:
	float _maxSpeed;
	Vector3D _forward;

};
#endif //!_CAR_H
