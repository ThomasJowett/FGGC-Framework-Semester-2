#pragma once

#include "Camera.h"

class OrbitCamera : public Camera
{
public:
	OrbitCamera();
	//OrbitCamera(Vector position, Vector at, Vector up, FLOAT fovY, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);
	~OrbitCamera();

	// Rotate the camera.
	void Pitch(float angle);
	void Yaw(float angle);

	void Update(Vector3D target);
	void SetDistance(FLOAT d);

private:
	float _distance = 300.0f;
	float _yaw;
	float _pitch;
};

