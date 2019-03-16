#pragma once

#include <vector>
#include <string>

#include "Object.h"

void application_initialize();
void application_run();
float application_elapsed_time();
float application_frames_per_second();
_STD vector<Object> *application_get_objects();
Object *application_create_object(_STD string name);