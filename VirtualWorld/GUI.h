#pragma once

#include <string>

#include "Vector2.h"
#include "Color.h"

void gui_draw_string(Vector2 pos, _STD wstring str);
void gui_draw_line(Vector2 start, Vector2 end, wchar_t ch = 0x2588, Color color = COLOR_FG_WHITE);
void gui_draw_triangle(Vector2 p1, Vector2 p2, Vector2 p3, wchar_t ch = 0x2588, Color color = COLOR_FG_WHITE);