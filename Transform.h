#pragma once
#include "Vector.h"
#include <directxmath.h>

using namespace::DirectX;

class Transform
{
public:
	Transform();
	Transform(Vector position, Vector rotation, Vector scale);
	~Transform() {};

	void SetPosition(Vector position)	{ _position = position; }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

	void SetRotation(Vector rotation)	{ _position = rotation; }
	void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	void SetScale(Vector scale)			{ _position = scale; }
	void SetScale(float x, float y, float z)	{ _scale.x = x; _scale.y = y; _scale.z = z; }

	void SetWorldMatrix4x4(XMFLOAT4X4 world) { _world = world; }

	Vector GetPosition() const { return _position; }
	Vector GetRotation() const { return _rotation; }
	Vector GetScale() const    { return _scale; }
	XMMATRIX GetWorldMatrix() const{return XMLoadFloat4x4(&_world);}
	XMFLOAT4X4 GetWorldMatrix4x4() const { return _world; }

	void UpdateWorldMatrix();

private:
	Vector _position;
	Vector _rotation;
	Vector _scale;

	XMFLOAT4X4 _world;
};
