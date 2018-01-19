#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Initialise(Vector position, Vector at, Vector up, FLOAT fovY, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth)
{
	SetLens(fovY, windowHeight, windowWidth, nearDepth, farDepth);
	SetLookAt(at);
	SetPosition(position);
	SetUp(up);
}

void Camera::SetLens(float fovY, float windowHeight, float windowWidth, float nearDepth, float farDepth)
{
	//Cache properties
	_fovY = fovY;
	_windowHeight = windowHeight;
	_windowWidth = windowWidth;
	_nearDepth = nearDepth;
	_farDepth = farDepth;

	// Initialize the projection matrix
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(fovY,  windowWidth / windowHeight, nearDepth, farDepth));
}

void Camera::Strafe(float d)
{
}

void Camera::Walk(float d)
{
}

void Camera::Raise(float d)
{
}

void Camera::Pitch(float angle)
{
}

void Camera::Yaw(float angle)
{
}

void Camera::Update()
{
    // Initialize the view matrix

	XMFLOAT4 eye = XMFLOAT4(_eye.x, _eye.y, _eye.z, 1.0f);
	XMFLOAT4 at = XMFLOAT4(_at.x, _at.y, _at.z, 1.0f);
	XMFLOAT4 up = XMFLOAT4(_up.x, _up.y, _up.z, 0.0f);

	XMVECTOR EyeVector = XMLoadFloat4(&eye);
	XMVECTOR AtVector = XMLoadFloat4(&at);
	XMVECTOR UpVector = XMLoadFloat4(&up);

	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(EyeVector, AtVector, UpVector));
}

void Camera::Reshape(FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;
}

XMFLOAT4X4 Camera::GetViewProjection() const 
{ 
	XMMATRIX view = XMLoadFloat4x4(&_view);
	XMMATRIX projection = XMLoadFloat4x4(&_projection);

	XMFLOAT4X4 viewProj;

	XMStoreFloat4x4(&viewProj, view * projection);

	return viewProj;
}