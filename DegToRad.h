#pragma once
#include "Header.h"

float deg_to_rad(float i_degrees)
{
	// Перевод из градусов в радианы
	return PI * i_degrees / 180;
}

float get_degrees(float i_degrees)
{
	return static_cast<float>(fmod(360 + fmod(i_degrees, 360), 360));
}