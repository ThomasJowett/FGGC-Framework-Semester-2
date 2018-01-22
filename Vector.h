#pragma once

#include <math.h>

class Vector
{
public:
	float x;
	float y;
	float z;

	Vector();
	Vector(float x, float y, float z);

	float GetMagnitude();
	float GetSqrMagnitude();
	Vector GetNormalized();
	void Normalize();

	static Vector Cross(Vector v1, Vector v2);
	static float Dot(Vector v1, Vector v2);
	static Vector Reflect(Vector vector, Vector normal);
	static Vector Replicate(float f);
	static Vector MultiplyAdd(Vector v1, Vector v2, Vector v3);

	//Operators
	Vector operator*(float scaler);
	Vector operator/(float scaler);
	Vector operator+(const Vector& other);
	Vector operator-(const Vector& other);
	Vector operator+=(const Vector& other);
	Vector operator-=(const Vector& other);
	bool operator==(const Vector& other);
	bool operator!=(const Vector& other);
	Vector operator=(const Vector& other);
};