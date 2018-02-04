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
	Vector s = Vector().Replicate(d);
	SetPosition(Vector().MultiplyAdd(s, GetRight(), GetPosition()));
}

void FreeLookCamera::Walk(float d)
{
	//mPosition += d*mLook
	Vector s = Vector().Replicate(d);
	SetPosition(Vector().MultiplyAdd(s, GetLook(), GetPosition()));
}

void FreeLookCamera::Raise(float d)
{
	//mPosition += d*mUp
	Vector s = Vector().Replicate(d);
	SetPosition(Vector().MultiplyAdd(s, GetUp(), GetPosition()));
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
	Vector R = GetRight();
	Vector U;
	Vector L = GetLook();
	Vector P = GetPosition();

	L.Normalize();
	R.Normalize();

	U = Vector().Cross(L, R).GetNormalized();
	R = Vector().Cross(U, L);

	SetRight(R);
	SetUp(U);
	SetLook(L);
	
	Camera::Update();
}
