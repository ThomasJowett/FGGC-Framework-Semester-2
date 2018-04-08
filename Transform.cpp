#include "Transform.h"

Transform::Transform()
{
	_position = Vector3D(0.0f, 0.0f, 0.0f);
	_rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	_scale = Vector3D(1.0f, 1.0f, 1.0f);
}

Transform::Transform(Vector3D position, Quaternion rotation, Vector3D scale)
{
	_position = position;
	_rotation = rotation;
	_scale = scale;
}

void Transform::UpdateWorldMatrix()
{
	
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);
	XMStoreFloat4x4(&_world, scale * CalculateTransformMatrix(_rotation) * translation);
}
