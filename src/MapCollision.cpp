#include <array>
#include <chrono>
#include "MapCollision.h"

//Коллизия, чтобы игрок не смог проходить через стены
bool map_collision(float i_x, float i_y, const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
	float cell_x = i_x / CELL_SIZE; // координата x в позиции в ячейке
	float cell_y = i_y / CELL_SIZE; // координата y в позиции в ячейке

	for (unsigned char a = 0; a < 4; a++)
	{
		short x = 0;
		short y = 0;

		switch (a)
		{
		case 0:
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(floor(cell_y));

			break;
		}
		case 1:
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(floor(cell_y));

			break;
		}
		case 2:
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(ceil(cell_y));

			break;
		}
		case 3:
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(ceil(cell_y));
		}
		}

		if (0 <= x && 0 <= y && MAP_HEIGHT > y && MAP_WIDTH > x)
		{
			if (Cell::Wall == i_map[x][y])
			{
				return 1;
			}
			if (Cell::Wall1 == i_map[x][y])
			{
				return 1;
			}
			if (Cell::Wall3 == i_map[x][y])
			{
				return 1;
			}
			if (Cell::Instruction == i_map[x][y])
			{
				return 1;
			}

		}
	}

	return 0;
}