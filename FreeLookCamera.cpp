#include "FreeLookCamera.h"



FreeLookCamera::FreeLookCamera()
{
}


FreeLookCamera::~FreeLookCamera()
{
}

void FreeLookCamera::Strafe(float d)
{
	// mPosition += d*mRight
	Vector3D s = Vector3D().Replicate(d);
	SetPosition(Vector3D().MultiplyAdd(s, GetRight(), GetPosition()));
}

void FreeLookCamera::Walk(float d)
{
	//mPosition += d*mLook
	Vector3D s = Vector3D().Replicate(d);
	SetPosition(Vector3D().MultiplyAdd(s, GetLook(), GetPosition()));
}

void FreeLookCamera::Raise(float d)
{
	//mPosition += d*mUp
	Vector3D s = Vector3D().Replicate(d);
	SetPosition(Vector3D().MultiplyAdd(s, GetUp(), GetPosition()));
}

void FreeLookCamera::Pitch(float angle)
{

	XMVECTOR right = { GetRight().x, GetRight().y, GetRight().z };
	XMMATRIX R = XMMatrixRotationAxis(right, angle);

	XMFLOAT3 up = { GetUp().x, GetUp().y, GetUp().z };
	XMFLOAT3 look = { GetLook().x, GetLook().y, GetLook().z };

	XMStoreFloat3(&up, XMVector3TransformNormal(XMLoadFloat3(&up), R));
	XMStoreFloat3(&look, XMVector3TransformNormal(XMLoadFloat3(&look), R));

	SetUp({ up.x, up.y, up.z });
	SetLook({ look.x, look.y, look.z });
	
}

void FreeLookCamera::Yaw(float angle)
{
	XMMATRIX R = XMMatrixRotationY(angle);

	XMFLOAT3 right = { GetRight().x, GetRight().y, GetRight().z };
	XMFLOAT3 look = { GetLook().x, GetLook().y, GetLook().z };

	XMStoreFloat3(&right, XMVector3TransformNormal(XMLoadFloat3(&right), R));
	XMStoreFloat3(&look, XMVector3TransformNormal(XMLoadFloat3(&look), R));

	SetLook({ look.x, look.y, look.z });
	SetRight({ right.x, right.y, right.z });
}

void FreeLookCamera::Update()
{
	Vector3D R = GetRight();
	Vector3D U;
	Vector3D L = GetLook();
	Vector3D P = GetPosition();

	L.Normalize();
	R.Normalize();

	U = Vector3D().Cross(L, R).GetNormalized();
	R = Vector3D().Cross(U, L);

	SetRight(R);
	SetUp(U);
	SetLook(L);
	
	Camera::Update();
}
