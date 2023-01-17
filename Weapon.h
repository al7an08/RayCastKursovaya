#pragma once
#include "SFML/Graphics.hpp"

class Weapon
{
private:
	unsigned int ammo;
	unsigned int magazine;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture fire_t;
	sf::Sprite fire_s;
	bool is_fire = false;
public:
	Weapon(unsigned int i_ammo, unsigned i_magazine);
	void fire();
	void draw(sf::RenderWindow& window);
};

