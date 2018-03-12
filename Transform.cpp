#include "Transform.h"

Transform::Transform()
{
	_position = Vector(0.0f, 0.0f, 0.0f);
	_rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	_scale = Vector(1.0f, 1.0f, 1.0f);
}

Transform::Transform(Vector position, Quaternion rotation, Vector scale)
{
	_position = position;
	_rotation = rotation;
	_scale = scale;
}

void Transform::UpdateWorldMatrix()
{
	
	// Calculate world matrix
	//XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	//XMMATRIX rotation = XMMatrixRotationX(_rotation.x) * XMMatrixRotationY(_rotation.y) * XMMatrixRotationZ(_rotation.z);
	//XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);

	XMStoreFloat4x4(&_world, CalculateTransformMatrix(_position, _rotation));

	//XMStoreFloat4x4(&_world, scale * rotation * translation);
}
