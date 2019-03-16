/*

DIRTYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY 
JUST FOR TESTING PURPOSES

*/

#include "Graph.h"
#include "GUI.h"
#include "Renderer.h"
#include "Matrix.h"
#include "Math.h"
#include "Time.h"


Graph::Graph()
{
	GraphObject gobj = GraphObject{
		3,
		new Vector2[3] {
			Vector2(10.f, 100.f), Vector2(120.f, 67.f), Vector2(43.f, 30.f)
		}
	};

	gobj.TargetVertices = new Vector2[gobj.VertexCount];
	Matrix posMatrix = matrix_from_vectors(gobj.Vertices, gobj.VertexCount);
	Matrix rotationMatrix = matrix_construct(2, 2, new float* [2]{ new float[2] { 0.f, 1.f }, new float[2] { -1.f, 0.f } });
	Matrix rotPosMatrix = rotationMatrix * posMatrix;
	for (unsigned int i = 0; i < gobj.VertexCount; i++)
	{
		gobj.TargetVertices[i] = Vector2(rotPosMatrix.vals[0][i], rotPosMatrix.vals[1][i]);
	}

	m_Objects.push_back(gobj);
}

Vector2 Fix(Vector2 v)
{
	return Vector2(renderer_get_screen_size().x / 2.f + v.x, renderer_get_screen_size().y / 2.f - v.y);
}

float timeLeft = 3.f;

float prog = 0.f;


void Graph::Update()
{
	Vector2 ssize = renderer_get_screen_size();
	gui_draw_line(Vector2(0.f, ssize.y / 2.f), Vector2(ssize.x, ssize.y / 2.f), L'.');
	gui_draw_line(Vector2(ssize.x / 2.f, 0.f), Vector2(ssize.x / 2.f, ssize.y), L'.');
	for (GraphObject& go : m_Objects)
	{
		for (unsigned int i = 0; i < go.VertexCount; i++)
		{
			unsigned int next = i + 1;
			if (next == go.VertexCount)
				next = 0;
			prog += time_deltatime();
			go.Vertices[i].x = math_move_towards(go.Vertices[i][0], go.TargetVertices[i][0], prog);
			go.Vertices[i].y = math_move_towards(go.Vertices[i][1], go.TargetVertices[i][1], prog);
			timeLeft -= time_deltatime();
			if (prog >= 1.f)
			{
				prog = 0.f;
				timeLeft = 3.f;
				//memcpy(go.Vertices, go.TargetVertices, sizeof(Vector2) * go.VertexCount);
				Matrix posMatrix = matrix_from_vectors(go.Vertices, go.VertexCount);
				Matrix rotationMatrix = matrix_construct(2, 2, new float* [2]{ new float[2] { 0.f, 1.f }, new float[2] { -1.f, 0.f } });
				Matrix rotPosMatrix = rotationMatrix * posMatrix;
				for (unsigned int i = 0; i < go.VertexCount; i++)
				{
					go.TargetVertices[i] = Vector2(rotPosMatrix.vals[0][i], rotPosMatrix.vals[1][i]);
				}
			}
			gui_draw_line(Fix(go.Vertices[i]), Fix(go.Vertices[next]));

			gui_draw_line(Fix(go.TargetVertices[i]), Fix(go.TargetVertices[next]), 96080U, COLOR_FG_BLUE);
		}
	}
	// 0 1
	//-1 0
}
