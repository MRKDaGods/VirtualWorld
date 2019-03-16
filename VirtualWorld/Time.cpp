#include "Time.h"
#include "Application.h"

float time_deltatime()
{
	return application_elapsed_time();
}
