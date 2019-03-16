#include "Vector2.h"
#include "Rect.h"
#include "Matrix.h"
#include "Math.h"
#include "Utils.h"
#include "Vector3.h"
#include "Quaternion.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <cstring>

const float math_pi = M_PI;

//VECTOR2

Vector2::Vector2() : Vector2(0.f, 0.f)
{
}

float Vector2::magnitude()
{
	return sqrtf(x * x + y * y);
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2 Vector2::operator-(Vector2 rhs)
{
	return Vector2(x - rhs.x, y - rhs.y);
}

float Vector2::operator[](unsigned int idx)
{
	return !idx ? x : idx ? y : 0.f;
}

//VECTOR3

Vector3::Vector3() : Vector3(0.f, 0.f, 0.f)
{
}

float Vector3::magnitude()
{
	return sqrtf(x * x + y * y + z * z);
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3 Vector3::operator-(Vector3 rhs)
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

float Vector3::operator[](unsigned int idx)
{
	return !idx ? x : idx ? y : idx == 2 ? z : 0.f;
}

//RECT

Rect::Rect() : Rect(0.f, 0.f, 0.f, 0.f)
{
}

Rect::Rect(float _x, float _y, float _w, float _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

//MATRIX

Matrix Matrix::operator*(Matrix m2)
{
	if (ordery != m2.orderx)
		return matrix_construct_identity(2);
	Matrix r = matrix_construct(orderx, m2.ordery, 0);
	for (unsigned int i = 0; i < r.orderx; i++)
	{
		for (unsigned j = 0; j < r.ordery; j++)
		{
			r.vals[i][j] = 0.f;
			for (unsigned int k = 0; k < ordery; k++)
				r.vals[i][j] += vals[i][k] * m2.vals[k][j];
		}
	}
	return r;
}

Vector3 Matrix::operator*(Vector3 vec)
{
	if (matrix_is_uniform(*this) && orderx == 4)
	{
		Vector3 v;
		v.x = vec.x * vals[0][0] + vec.y * vals[1][0] + vec.z * vals[2][0] + vals[3][0];
		v.y = vec.x * vals[0][1] + vec.y * vals[1][1] + vec.z * vals[2][1] + vals[3][1];
		v.z = vec.x * vals[0][2] + vec.y * vals[1][2] + vec.z * vals[2][2] + vals[3][2];
		float w = vec.x * vals[0][3] + vec.y * vals[1][3] + vec.z * vals[2][3] + vals[3][3];
		if (w != 0.f)
			v.x /= w; v.y /= w; v.z /= w;
		return v;
	}
	return Vector3();
}

Matrix matrix_construct_identity(unsigned int order)
{
	Matrix m = matrix_construct(order, order, 0);
	for (unsigned int i = 0; i < order; i++)
		m.vals[i][i] = 1.f;
	return m;
}

void matrix_zero(Matrix &matrix)
{
	ReAlloc<float*>(&matrix.vals, matrix.orderx, matrix.orderx);
	for (unsigned int i = 0; i < matrix.orderx; i++)
	{
		ReAlloc<float>(&matrix.vals[i], matrix.ordery, matrix.ordery);
		for (unsigned int j = 0; j < matrix.ordery; j++)
			matrix.vals[i][j] = 0.f;
	}
}

bool matrix_is_uniform(Matrix &matrix)
{
	return matrix.orderx == matrix.ordery;
}

Matrix matrix_construct(unsigned int x, unsigned int y, float **vals)
{
	Matrix m = Matrix{
		x,
		y,
		0
	};
	matrix_zero(m);
	if (vals)
		memcpy(m.vals, vals, sizeof(float) * x * y);
	return m;
}

Matrix matrix_from_vectors(Vector2 *arr, unsigned int len)
{
	Matrix m = matrix_construct(2, len, 0);
	for (unsigned int col = 0; col < len; col++)
	{
		for (unsigned int row = 0; row < 2; row++)
		{
			m.vals[row][col] = arr[col][row];
		}
	}
	return m;
}

//QUATERNION

Quaternion::Quaternion() : Quaternion(1.f, 0.f, 0.f, 0.f)
{	
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
	w = _w;
	x = _x;
	y = _y;
	z = _z;
}

//OTHER

float math_move_towards(float current, float target, float maxDelta)
{
	if (fabsf(target - current) <= maxDelta)
		return target;
	return current + math_sign(target - current) * maxDelta;
}

float math_sign(float val)
{
	return val > 0.f ? 1.f : -1.f;
}
