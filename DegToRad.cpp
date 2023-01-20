#include <chrono>

#include "DegToRad.h"
#include "Header.h"

float deg_to_rad(float i_degrees)
{
	//Функция, которая получает на вход градусы и переводит их в радианы
	return PI * i_degrees / 180;
}