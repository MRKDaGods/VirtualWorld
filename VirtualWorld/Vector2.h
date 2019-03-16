#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2(float _x, float _y);
	Vector2();
	float magnitude();

	Vector2 operator -(Vector2 rhs);
	float operator [](unsigned int idx);
};