#pragma once

#include <cstring>

template<typename T>
inline void ReAlloc(T** arr, unsigned int sz, unsigned int newSz)
{
	//static_assert(newSz > sz && arr);
	T* newAlloc = new T[newSz];
	if (*arr && *arr != (void*)0xcdcdcdcd) //debug
	{
		memcpy(newAlloc, *arr, sizeof(T) * sz);
		//delete[] * arr;
	}
	*arr = newAlloc;
}