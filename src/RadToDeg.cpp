#include <chrono>

#include "RadToDeg.h"
#include "Header.h"

float rad_to_deg(float i_radians)
{
	return 180 * i_radians / PI;
}