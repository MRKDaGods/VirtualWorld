#include "Transform.h"

Vector3 &Transform::Position()
{
	return m_Position;
}

Quaternion &Transform::Rotation()
{
	return m_Rotation;
}

void Transform::Update()
{
}
