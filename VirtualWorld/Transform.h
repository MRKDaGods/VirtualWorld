#pragma once

#include "Component.h"
#include "Vector3.h"
#include "Quaternion.h"

class Transform : public Component
{
private:
	Vector3 m_Position;
	Quaternion m_Rotation;
public:
	Vector3 &Position();
	Quaternion &Rotation();
	void Update() override;
};