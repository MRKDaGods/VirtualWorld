#include "Renderer.h"
#include "ExplicitConversions.h"

#include <Windows.h>

void **renderer_console_handle_io;

Vector2 renderer_screen_size;
Vector2 renderer_screen_resolution;
Rect renderer_screen_rect;

unsigned int renderer_pixel_count;
CHAR_INFO *renderer_pixels;

void renderer_initialize(const char *title, Vector2 screenSize, Vector2 screenRes)
{
	renderer_console_handle_io = new void* [2] {
		GetStdHandle(STD_INPUT_HANDLE),
		GetStdHandle(STD_OUTPUT_HANDLE)
	};
	SetConsoleTitleA(title);
	renderer_screen_size = screenSize;
	renderer_screen_resolution = screenRes;
	renderer_screen_rect = Rect(0.f, 0.f, renderer_screen_size.x - 1, renderer_screen_size.y - 1);
	SMALL_RECT rect = Conversions<Rect, SMALL_RECT>::Convert(Rect(0.f, 0.f, 1.f, 1.f));
	SetConsoleWindowInfo(renderer_console_handle_io[1], true, &rect);
	SetConsoleScreenBufferSize(renderer_console_handle_io[1], Conversions<Vector2, COORD>::Convert(renderer_screen_size));
	SetConsoleActiveScreenBuffer(renderer_console_handle_io[1]);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 4;
	cfi.dwFontSize.Y = 4;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(renderer_console_handle_io[1], false, &cfi);

	rect = Conversions<Rect, SMALL_RECT>::Convert(renderer_screen_rect);
	SetConsoleWindowInfo(renderer_console_handle_io[1], true, &rect);
	SetConsoleMode(renderer_console_handle_io[0], ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	renderer_pixel_count = (unsigned int)(renderer_screen_size.x * renderer_screen_size.y);
	renderer_pixels = new CHAR_INFO[renderer_pixel_count];
	memset(renderer_pixels, 0, renderer_pixel_count * sizeof(CHAR_INFO));
}

void renderer_flush()
{
	for (unsigned int i = 0; i < renderer_pixel_count; i++)
		renderer_pixels[i].Char.UnicodeChar = L'\x20';
}

void renderer_render()
{
	SMALL_RECT rect = Conversions<Rect, SMALL_RECT>::Convert(renderer_screen_rect);
	WriteConsoleOutputW(renderer_console_handle_io[1], renderer_pixels, Conversions<Vector2, COORD>::Convert(renderer_screen_size), { 0, 0 }, &rect);
}

void *renderer_get_pixels()
{
	return renderer_pixels;
}

unsigned int renderer_get_pixel_count()
{
	return renderer_pixel_count;
}

void renderer_set_pixel(unsigned int x, unsigned int y, wchar_t ch, Color color)
{
	if (x >= 0 && x < renderer_screen_size.x && y >= 0 && y < renderer_screen_size.y)
	{
		renderer_pixels[y * (unsigned int)renderer_screen_size.x + x].Char.UnicodeChar = ch;
		renderer_pixels[y * (unsigned int)renderer_screen_size.x + x].Attributes = color;
	}
}

Vector2 renderer_get_screen_size()
{
	return renderer_screen_size;
}
