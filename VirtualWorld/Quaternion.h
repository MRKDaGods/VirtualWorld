#pragma once

struct Quaternion
{
	float w;
	float x;
	float y;
	float z;

	Quaternion(float _w, float _x, float _y, float _z);
	Quaternion();
};