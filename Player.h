#pragma once
#include "Header.h"
#include "SFML/Graphics.hpp"
#include "Weapon.h"
#include "DegToRad.h"
#include "Enemy.h"
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
	Weapon& gun;
	std::array<float, SCREEN_WIDTH> view_rays;

	sf::Sprite map_player_sprite;
	sf::Texture map_player_texture;

	sf::Sprite wall_sprite;
	sf::Texture wall_texture;


	sf::Texture wall_texture1;
	sf::Sprite wall_sprite1;

	sf::Sprite enemy_sprite;
	sf::Texture enemy_texture;
public:
	Player(float i_x, float i_y, float hp, Weapon& i_gun);

	void draw_map(sf::RenderWindow& i_window);
	void draw_screen(sf::RenderWindow& i_window, const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, const Enemy& enemy);
	void set_position(float i_x, float i_y);
	void update(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, const sf::RenderWindow& i_window);
};

