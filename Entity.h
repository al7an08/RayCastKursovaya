#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "Header.h"
#include <iostream>
#include <string>
#include "Player.h"

class Entity{
	std::string name;
	sf::Sprite map_entity_sprite;

	sf::Texture map_entity_texture;
public:
	Entity(float i_x, float i_y);

	float get_center_x() const;
	float get_center_y() const;
	float get_direction() const;

	void draw_map(sf::RenderWindow& i_window);
	void set_position(float i_x, float i_y);
	void update(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, const sf::RenderWindow& i_window);

};

