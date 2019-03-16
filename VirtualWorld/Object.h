#pragma once

#include <vector>
#include <string>
#include <map>
#include <typeinfo>

#include "Component.h"

class Object
{
private:
	_STD map<_STD string, Component*> m_Components;
	_STD string m_Name;
public:
	static Object *FindObjectWithName(_STD string name);

	Object(_STD string name);
	Object();
	void Pulse();

	template<class T>
	T *GetComponent()
	{
		T local;
		Component *cmp = dynamic_cast<Component*>(&local);
		if (!cmp)
			_STD _Xruntime_error("Class is not Component");
		auto src = m_Components.find(typeid(T).name());
		if (src != m_Components.end())
			return (T*)src->second;
		return 0;
	}

	template<class T>
	T *AddComponent()
	{
		T local;
		Component *cmp = dynamic_cast<Component*>(&local);
		//if (!cmp)
		//	_STD _Xruntime_error("Class is not Component");
		m_Components.insert({ _STD string(typeid(T).name()), (Component*)new T });
		return (T*)m_Components.at(typeid(T).name());
	}
};