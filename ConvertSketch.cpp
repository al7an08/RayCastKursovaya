#include "ConvertSketch.h"
#include "SFML/Graphics.hpp"
#include <array>


// Создание уровня из изображения, цвет каждого пикселя соответсвует с одним из объектов, а его расположение соответсвует расположению на карте
std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(Player& i_player, Enemy& enemy)
{
	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> output_map{};

	sf::Image map_sketch;
	map_sketch.loadFromFile("Resources/Images/MapSketch.png");

	for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
			sf::Color pixel = map_sketch.getPixel(a, b);

			if (pixel == sf::Color(0, 0, 0))
			{
				output_map[a][b] = Cell::Wall;
			}
			else if (pixel == sf::Color(255, 0, 0))
			{
				i_player.set_position(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));
			}
			else if (pixel == sf::Color(0, 0, 255))
			{
				enemy.set_position(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));
			}
			else if (pixel == sf::Color(255, 0, 255))
			{
				output_map[a][b] = Cell::Wall1;
			}
			else 
			{
				output_map[a][b] = Cell::Empty;
			}
		}
	}

	return output_map;
}