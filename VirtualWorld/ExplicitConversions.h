#pragma once

#include <Windows.h>

#include "Rect.h"
#include "Vector2.h"
#include "Vector3.h"

template<typename src, typename dest>
class Conversions
{
public:
	static dest Convert(src val) 
	{
	}
};

template<>
class Conversions<Rect, RECT>
{
public:
	static RECT Convert(Rect val)
	{
		return { (long)val.x, (long)val.y, (long)val.w, (long)val.h };
	}
};

template<>
class Conversions<Rect, SMALL_RECT>
{
public:
	static SMALL_RECT Convert(Rect val)
	{
		return { (short)val.x, (short)val.y, (short)val.w, (short)val.h };
	}
};

template<>
class Conversions<Vector2, COORD>
{
public:
	static COORD Convert(Vector2 val)
	{
		return { (short)val.x, (short)val.y };
	}
};

template<>
class Conversions<Vector3, Vector2>
{
public:
	static Vector2 Convert(Vector3 val)
	{
		return Vector2(val.x, val.y);
	}
};