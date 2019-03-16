#pragma once

#include "Vector2.h"
#include "Color.h"

void renderer_initialize(const char *title, Vector2 screenSize, Vector2 screenRes);
void renderer_flush();
void renderer_render();
void *renderer_get_pixels();
unsigned int renderer_get_pixel_count();
void renderer_set_pixel(unsigned int x, unsigned int y, wchar_t ch, Color color);
Vector2 renderer_get_screen_size();