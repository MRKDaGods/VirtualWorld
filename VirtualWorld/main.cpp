#include "Application.h"

int main()
{
	application_initialize();
	while (true) {
		application_run();
	}
	/*auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();
	Graph graph;
	while (true)
	{
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();
		renderer_flush();
		
		graph.Render();

		wchar_t s[256];
		swprintf_s(s, 256, L"FPS: %3.2f", 1.f / fElapsedTime);
		SetConsoleTitle(s);

		renderer_render();
	}*/
	return 0;
}