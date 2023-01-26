#pragma once
#include "Header.h"
#include "SFML/Graphics.hpp"
#include "DegToRad.h"
#include <array>


class Player
{
private:
	float direction_horizontal;
	float direction_vertical;
	double planeX = 0.0, planeY = 0.66;
	double dirX = -1.0, dirY = 0.0;
	float x;
	float y;
	float hp;
	std::array<float, SCREEN_WIDTH> view_rays;

	sf::Sprite map_player_sprite;
	sf::Texture map_player_texture;

	std::array<sf::Texture, NUM_WALL_TYPES> wall_textures;
	std::array<sf::Sprite, NUM_WALL_TYPES> wall_sprites;
	

	sf::Sprite enemy_sprite;
	sf::Texture enemy_texture;
public:
	Player(float i_x, float i_y, float hp);

	void draw_map(sf::RenderWindow& i_window);
	void draw_screen(sf::RenderWindow& i_window, const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
	void set_position(float i_x, float i_y);
	void update(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, const sf::RenderWindow& i_window);
};

