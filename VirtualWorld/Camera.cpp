#include "Camera.h"
#include "Renderer.h"
#include "Math.h"
#include "ExplicitConversions.h"

#include <math.h>

void Camera::UpdateProjection()
{
	float fovrad = 1.f / tanf(m_Fov / 2.f / 180.f * math_pi);
	m_Projection.vals[0][0] = m_AspectRatio * fovrad;
	m_Projection.vals[1][1] = fovrad;
	m_Projection.vals[2][2] = m_Far / (m_Far - m_Near);
	m_Projection.vals[3][2] = (-m_Far * m_Near) / (m_Far - m_Near);
	m_Projection.vals[2][3] = 1.f;
}

Camera::Camera(float fov, float _near, float _far)
{
	m_Fov = fov;
	m_Near = _near;
	m_Far = _far;
	m_AspectRatio = renderer_get_screen_size().x / renderer_get_screen_size().y;
	m_Projection = matrix_construct(4, 4, 0);
	UpdateProjection();
}

Camera::Camera()
{
}

void Camera::Update()
{
}

Vector2 Camera::WorldToUIPoint(Vector3 world)
{
	return Conversions<Vector3, Vector2>::Convert(m_Projection * world);
}
