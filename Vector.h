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
	float GetSqrMagnitude();
	Vector GetNormalized();
	void Normalize();
	Vector Cross(Vector v1, Vector v2);
	float Dot(Vector v1, Vector v2);
	Vector Reflect(Vector vector, Vector normal);
	
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