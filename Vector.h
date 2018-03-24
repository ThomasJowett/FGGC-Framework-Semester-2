#pragma once

#include <math.h>

class Vector3D
{
public:
	float x;
	float y;
	float z;

	Vector3D();
	Vector3D(float x, float y, float z);

	float GetMagnitude();
	float GetSqrMagnitude();
	Vector3D GetNormalized();
	void Normalize();

	static Vector3D Cross(Vector3D v1, Vector3D v2);
	static float Dot(Vector3D v1, Vector3D v2);
	static Vector3D Reflect(Vector3D vector, Vector3D normal);
	static Vector3D Replicate(float f);
	static Vector3D MultiplyAdd(Vector3D v1, Vector3D v2, Vector3D v3);

	//Operators
	Vector3D operator*(float scaler);
	Vector3D operator/(float scaler);
	Vector3D operator+(const Vector3D& other);
	Vector3D operator-(const Vector3D& other);
	Vector3D operator+=(const Vector3D& other);
	Vector3D operator-=(const Vector3D& other);
	bool operator==(const Vector3D& other);
	bool operator!=(const Vector3D& other);
	Vector3D operator=(const Vector3D& other);
};