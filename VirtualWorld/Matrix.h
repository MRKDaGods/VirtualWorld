#pragma once

#include "Vector2.h"
#include "Vector3.h"

struct Matrix
{
	unsigned int orderx;
	unsigned int ordery;
	float **vals;

	Matrix operator*(Matrix m2);
	Vector3 operator*(Vector3 vec);
};

Matrix matrix_construct_identity(unsigned int order);
void matrix_zero(Matrix &matrix);
bool matrix_is_uniform(Matrix &matrix);
Matrix matrix_construct(unsigned int x, unsigned int y, float **vals);;
Matrix matrix_from_vectors(Vector2 *arr, unsigned int len);