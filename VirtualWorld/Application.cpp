#include "Application.h"
#include "Renderer.h"
#include "Camera.h"
#include "TestProjection.h"

#include <chrono>
#include <vector>
#include <Windows.h>

auto application_tp1 = _STD chrono::system_clock::now();
auto application_tp2 = _STD chrono::system_clock::now();
float application_elapsed = 0.f;
float application_fps = 0.f;
_STD vector<Object> application_objects;

void application_initialize()
{
	renderer_initialize("Virtual World", Vector2(256.f, 240.f), Vector2());

	//init camera
	Object *cameraObj = application_create_object("Main Camera");
	*cameraObj->AddComponent<Camera>() = Camera(90.f, 0.1f, 1000.f);

	//init test
	application_create_object("Test Projection")->AddComponent<TestProjection>();
}

void application_run()
{
	application_tp2 = _STD chrono::system_clock::now();
	application_elapsed = ((_STD chrono::duration<float>)(application_tp2 - application_tp1)).count();
	application_tp1 = application_tp2;
	application_fps = 1.f / application_elapsed;

	renderer_flush();
	for (Object &obj : application_objects)
		obj.Pulse();
	wchar_t s[256];

	swprintf_s(s, 256, L"FPS: %3.2f", 1.f / application_elapsed);
	SetConsoleTitleW(s);
	renderer_render();
}

float application_elapsed_time()
{
	return application_elapsed;
}

float application_frames_per_second()
{
	return application_fps;
}

_STD vector<Object> *application_get_objects()
{
	return &application_objects;
}

Object *application_create_object(_STD string name)
{
	application_objects.push_back(name.empty() ? Object() : Object(name));
	return &application_objects.back();
}
