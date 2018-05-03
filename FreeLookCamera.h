#pragma once
#include "Camera.h"
class FreeLookCamera : public Camera
{
public:
	FreeLookCamera();
	~FreeLookCamera();

	void Strafe(float d);
	void Walk(float d);
	void Raise(float d);

	void Pitch(float angle);
	void Yaw(float angle);

	void Update(Vector3D target);
};

