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
	float x;
	float y;
	float hp;
	Weapon& gun;
	std::array<float, SCREEN_WIDTH> view_rays;

	sf::Sprite map_player_sprite;
	sf::Sprite enemy_sprite;
	sf::Sprite wall_sprite;

	sf::Texture map_player_texture;
	sf::Texture wall_texture;
	sf::Texture enemy_texture;
public:
	Player(float i_x, float i_y, float hp, Weapon& i_gun);

	void draw_map(sf::RenderWindow& i_window);
	void draw_screen(sf::RenderWindow& i_window, const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, const Enemy& enemy);
	void set_position(float i_x, float i_y);
	void update(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, const sf::RenderWindow& i_window);
};

