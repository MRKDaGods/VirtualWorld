#pragma once

#include <vector>

#include "Vector2.h"
#include "Component.h"

class Graph : public Component
{
private:
	struct GraphObject
	{
		unsigned int VertexCount;
		Vector2 *Vertices;
		Vector2 *TargetVertices;
	};

	_STD vector<GraphObject> m_Objects;
public:
	Graph();
	void Update() override;
};