#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "Vector.h"

using namespace DirectX;

class Camera
{
private:
	Vector3D _eye; 
	Vector3D _at;
	Vector3D _up;
	Vector3D _right;
	Vector3D _look;

	FLOAT _windowWidth;
	FLOAT _windowHeight;
	FLOAT _nearDepth;
	FLOAT _farDepth;
	FLOAT _fovY;

	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;


public:
	Camera();
	~Camera();

	void Initialise(Vector3D position, Vector3D at, Vector3D up, FLOAT fovY, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);

	virtual void Strafe(float d) {};
	virtual void Walk(float d) {};
	virtual void Raise(float d) {};

	// Rotate the camera.
	virtual void Pitch(float angle) {};
	virtual void Yaw(float angle) {};

	virtual void Update(Vector3D target);

	XMFLOAT4X4 GetView() const { return _view; }
	XMFLOAT4X4 GetProjection() const { return _projection; }

	XMFLOAT4X4 GetViewProjection() const;

	Vector3D GetPosition() const { return _eye; }
	Vector3D GetLookAt() const { return _at; }
	Vector3D GetUp() const { return _up; }
	Vector3D GetRight() const { return _right; }
	Vector3D GetLook() const { return _look; }

	void SetLens(float fovY, float windowHeight, float windowWidth, float zn, float zf);
	void SetPosition(Vector3D position) { _eye = position; }
	void SetLookAt(Vector3D lookAt) { _at = lookAt; }
	void SetUp(Vector3D up) { _up = up; }
	void SetRight(Vector3D right) { _right = right; }
	void SetLook(Vector3D look) { _look = look; }

	void Reshape(FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);
};

