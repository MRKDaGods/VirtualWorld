#pragma once

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(float _x, float _y, float _z);
	Vector3();
	float magnitude();

	Vector3 operator -(Vector3 rhs);
	float operator [](unsigned int idx);
};