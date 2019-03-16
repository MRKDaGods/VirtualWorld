#pragma once

#include "Component.h"
#include "Matrix.h"
#include "Vector2.h"
#include "Vector3.h"

class Camera : public Component
{
private:
	float m_Fov;
	float m_Near;
	float m_Far;
	float m_AspectRatio;
	Matrix m_Projection;

	void UpdateProjection();
public:
	Camera(float fov, float _near, float _far);
	Camera();
	void Update() override;
	Vector2 WorldToUIPoint(Vector3 world);
};