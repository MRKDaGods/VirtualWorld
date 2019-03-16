#include "Object.h"
#include "Transform.h"
#include "Application.h"

Object *Object::FindObjectWithName(_STD string name)
{
	_STD vector<Object> *objs = application_get_objects();
	for (unsigned int i = 0; i < objs->size(); i++)
	{
		Object *current = &(*objs)[i];
		if (current->m_Name == name)
			return current;
	}
	return 0;
}

Object::Object(_STD string name) : m_Name(name)
{
	AddComponent<Transform>();
}

Object::Object() : Object("New Virtual Object")
{
}

void Object::Pulse()
{
	for (auto &c : m_Components)
		c.second->Update();
}
