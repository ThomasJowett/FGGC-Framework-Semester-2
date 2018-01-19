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
	Vector _eye; 
	Vector _at;
	Vector _up;

	FLOAT _windowWidth;
	FLOAT _windowHeight;
	FLOAT _nearDepth;
	FLOAT _farDepth;
	FLOAT _fovY;

	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;


public:
	Camera(Vector position, Vector at, Vector up, FLOAT fovY, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);
	~Camera();

	

	void Update();

	XMFLOAT4X4 GetView() const { return _view; }
	XMFLOAT4X4 GetProjection() const { return _projection; }

	XMFLOAT4X4 GetViewProjection() const;

	Vector GetPosition() const { return _eye; }
	Vector GetLookAt() const { return _at; }
	Vector GetUp() const { return _up; }

	void SetLens(float fovY, float windowHeight, float windowWidth, float zn, float zf);
	void SetLookAt(Vector position, Vector target, Vector worldUp);
	void SetPosition(Vector position) { _eye = position; }
	void SetLookAt(Vector lookAt) { _at = lookAt; }
	void SetUp(Vector up) { _up = up; }

	void Reshape(FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);
};

