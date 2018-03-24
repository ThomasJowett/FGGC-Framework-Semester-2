#include "Vector.h"


Vector3D::Vector3D()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3D::GetMagnitude()
{
	return sqrtf(GetSqrMagnitude());
}

float Vector3D::GetSqrMagnitude()
{
	return ((x*x) + (y*y) + (z*z));
}

Vector3D Vector3D::GetNormalized()
{
	float magnitude = GetMagnitude();
	return Vector3D(x / magnitude, y / magnitude, z / magnitude);
}

void Vector3D::Normalize()
{
	Vector3D normalized = GetNormalized();

	x = normalized.x;
	y = normalized.y;
	z = normalized.z;
}

Vector3D Vector3D::Cross(Vector3D v1, Vector3D v2)
{
	Vector3D cross;
	cross.x = (v1.y*v2.z) - (v1.z*v2.y);
	cross.y = -((v1.x*v2.z) - (v1.z*v2.x));
	cross.z = (v1.x*v2.y) - (v1.y*v2.x);
	return cross;
}

float Vector3D::Dot(Vector3D v1, Vector3D v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

Vector3D Vector3D::Reflect(Vector3D v, Vector3D normal)
{
	normal.Normalize();
	return v - (normal * (2.0f * Dot(v, normal)));
}

Vector3D Vector3D::Replicate(float f)
{
	return Vector3D(f,f,f);
}

Vector3D Vector3D::MultiplyAdd(Vector3D v1, Vector3D v2, Vector3D v3)
{
	Vector3D Result;

	Result.x = v1.x * v2.x + v3.x;
	Result.y = v1.y * v2.y + v3.y;
	Result.z = v1.z * v2.z + v3.z;

	return Result;
}

Vector3D Vector3D::operator*(float scaler)
{
	return Vector3D(x * scaler, y * scaler, z * scaler);
}

Vector3D Vector3D::operator/(float scaler)
{
	return Vector3D(x/scaler, y/scaler, z/scaler);
}

Vector3D Vector3D::operator+(const Vector3D & other)
{
	return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D & other)
{
	return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator+=(const Vector3D & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3D Vector3D::operator-=(const Vector3D & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

bool Vector3D::operator==(const Vector3D & other)
{
	if (x == other.x && y == other.y && z == other.z)
		return true;
	else
		return false;
}

bool Vector3D::operator!=(const Vector3D & other)
{
	if (x == other.x && y == other.y && z == other.z)
		return false;
	else
		return true;
}

Vector3D Vector3D::operator=(const Vector3D & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}
