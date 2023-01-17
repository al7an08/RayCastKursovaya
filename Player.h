#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Header.h"
#include <array>

class Player
{
private:
	float direction_horizontal;
	float direction_vertical;
	float x;
	float y;
	float hp;

	std::array<float, SCREEN_WIDTH> view_rays;

	sf::Sprite map_player_sprite;
	sf::Sprite steven_sprite;
	sf::Sprite wall_sprite;

	sf::Texture map_player_texture;
	sf::Texture wall_texture;
public:
	Player(float i_x, float i_y, float hp);

	void draw_map(sf::RenderWindow& i_window);
	void draw_screen(sf::RenderWindow& i_window, const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	void set_position(float i_x, float i_y);
	void update(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, const sf::RenderWindow& i_window);
};

