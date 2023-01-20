#include <chrono>

#include "GetDegrees.h"
#include "Header.h"

float get_degrees(float i_degrees)
{
	return static_cast<float>(fmod(360 + fmod(i_degrees, 360), 360));
}