#include "TestProjection.h"
#include "Mesh.h"
#include "GUI.h"
#include "Camera.h"
#include "Object.h"
#include "Renderer.h"

Mesh mesh = Mesh{
	{
			{ Vector3(0.0f, 0.0f, 0.0f),    Vector3(0.0f, 1.0f, 0.0f),    Vector3(1.0f, 1.0f, 0.0f) },
			{ Vector3(0.0f, 0.0f, 0.0f),    Vector3(1.0f, 1.0f, 0.0f),    Vector3(1.0f, 0.0f, 0.0f) },                                                     
			{ Vector3(1.0f, 0.0f, 0.0f),    Vector3(1.0f, 1.0f, 0.0f),    Vector3(1.0f, 1.0f, 1.0f) },
			{ Vector3(1.0f, 0.0f, 0.0f),    Vector3(1.0f, 1.0f, 1.0f),    Vector3(1.0f, 0.0f, 1.0f) },                                                   
			{ Vector3(1.0f, 0.0f, 1.0f),    Vector3(1.0f, 1.0f, 1.0f),    Vector3(0.0f, 1.0f, 1.0f) },
			{ Vector3(1.0f, 0.0f, 1.0f),    Vector3(0.0f, 1.0f, 1.0f),    Vector3(0.0f, 0.0f, 1.0f) },                                                    
			{ Vector3(0.0f, 0.0f, 1.0f),    Vector3(0.0f, 1.0f, 1.0f),    Vector3(0.0f, 1.0f, 0.0f) },
			{ Vector3(0.0f, 0.0f, 1.0f),    Vector3(0.0f, 1.0f, 0.0f),    Vector3(0.0f, 0.0f, 0.0f) },                                                     
			{ Vector3(0.0f, 1.0f, 0.0f),    Vector3(0.0f, 1.0f, 1.0f),    Vector3(1.0f, 1.0f, 1.0f) },
			{ Vector3(0.0f, 1.0f, 0.0f),    Vector3(1.0f, 1.0f, 1.0f),    Vector3(1.0f, 1.0f, 0.0f) },                                                  
			{ Vector3(1.0f, 0.0f, 1.0f),    Vector3(0.0f, 0.0f, 1.0f),    Vector3(0.0f, 0.0f, 0.0f) },
			{ Vector3(1.0f, 0.0f, 1.0f),	Vector3(0.0f, 0.0f, 0.0f),	  Vector3(1.0f, 0.0f, 0.0f) }
	}
};

TestProjection::TestProjection()
{
}

void TestProjection::Update()
{
	Camera *cam = Object::FindObjectWithName("Main Camera")->GetComponent<Camera>();
	for (_STD vector<Vector3> &tri : mesh.tris)
	{
		tri[0].z += 0.2f;
		tri[1].z += 0.2f;
		tri[2].z += 0.2f;
		Vector2 p1 = cam->WorldToUIPoint(tri[0]);
		Vector2 p2 = cam->WorldToUIPoint(tri[1]);
		Vector2 p3 = cam->WorldToUIPoint(tri[2]);
		p1.x += 1.0f; p1.y += 1.0f;
		p2.x += 1.0f; p2.y += 1.0f;
		p3.x += 1.0f; p3.y += 1.0f;
		p1.x *= 0.5f * renderer_get_screen_size().x;
		p1.y *= 0.5f * renderer_get_screen_size().y;
		p2.x *= 0.5f * renderer_get_screen_size().x;
		p2.y *= 0.5f * renderer_get_screen_size().y;
		p3.x *= 0.5f * renderer_get_screen_size().x;
		p3.y *= 0.5f * renderer_get_screen_size().y;
		gui_draw_triangle(p1, p2, p3);
	}
}
