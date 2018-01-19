#include "OrbitCamera.h"


OrbitCamera::OrbitCamera()
{
	_yaw = XM_PI;
	_pitch = -0.523599f;
}

OrbitCamera::~OrbitCamera()
{
}

void OrbitCamera::Pitch(float angle)
{
	_pitch -= angle;
	if (_pitch > (XM_PIDIV2 - 0.01))
		_pitch = (XM_PIDIV2 - 0.01);
	if (_pitch < (-XM_PIDIV2 + 0.01))
		_pitch = (-XM_PIDIV2 + 0.01);
}

void OrbitCamera::Yaw(float angle)
{
	_yaw -= angle;
	if (_yaw > XM_2PI || _yaw < -XM_2PI)
		_yaw = 0;
}

void OrbitCamera::Update()
{
	Vector position;
	position.x = GetLookAt().x + _distance * -sin(_yaw) * cos(_pitch);
	position.y = GetLookAt().y + _distance * -sin(_pitch);
	position.z = GetLookAt().z + _distance * cos(_yaw) * cos(_pitch);

	SetPosition(position);

	Camera::Update();
}

void OrbitCamera::SetDistance(FLOAT d)
{
	_distance = d;
}
