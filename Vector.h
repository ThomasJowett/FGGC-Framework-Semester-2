#pragma once
#include <directxmath.h>

class Vector
{
public:
	float x;
	float y;
	float z;

	Vector();
	Vector(float initialX, float initialY, float initialZ);

	float GetMagnitude();
	Vector GetNormalized();
	void Normalize();
	Vector Cross(Vector v1, Vector v2);
	Vector Dot(Vector v1, Vector v2);
	Vector operator*(float scaler);
	Vector operator+(const Vector& other);
	Vector operator+=(const Vector& other);
	Vector operator-=(const Vector& other);

};