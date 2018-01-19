#include "Vector.h"


Vector::Vector()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector::Vector(float initialX, float initialY, float initialZ)
{
	x = initialX;
	y = initialY;
	z = initialZ;
}

float Vector::GetMagnitude()
{
	return sqrtf(GetSqrMagnitude());
}

float Vector::GetSqrMagnitude()
{
	return ((x*x) + (y*y) + (z*z));
}

Vector Vector::GetNormalized()
{
	float magnitude = GetMagnitude();
	return Vector(x / magnitude, y / magnitude, z / magnitude);
}

void Vector::Normalize()
{
	x = GetNormalized().x;
	y = GetNormalized().y;
	z = GetNormalized().z;
}

Vector Vector::Cross(Vector v1, Vector v2)
{
	Vector cross;
	cross.x = (v1.y*v2.z) - (v1.z*v2.y);
	cross.y = -((v1.x*v2.z) - (v1.z*v2.x));
	cross.z = (v1.x*v2.y) - (v1.y*v2.x);
	return cross;
}

float Vector::Dot(Vector v1, Vector v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

Vector Vector::Reflect(Vector v, Vector normal)
{
	normal.Normalize();
	return v - (normal * (2.0f * Dot(v, normal)));
}

Vector Vector::operator*(float scaler)
{
	return Vector(x * scaler, y * scaler, z * scaler);
}

Vector Vector::operator/(float scaler)
{
	return Vector();
}

Vector Vector::operator+(const Vector & other)
{
	return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator-(const Vector & other)
{
	return Vector(x - other.x, y - other.y, z - other.z);
}

Vector Vector::operator+=(const Vector & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector Vector::operator-=(const Vector & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

bool Vector::operator==(const Vector & other)
{
	if (x == other.x && y == other.y && z == other.z)
		return true;
	else
		return false;
}

bool Vector::operator!=(const Vector & other)
{
	if (x == other.x && y == other.y && z == other.z)
		return false;
	else
		return true;
}

Vector Vector::operator=(const Vector & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}
