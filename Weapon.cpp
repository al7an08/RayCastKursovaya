#include "Weapon.h"
#include "Header.h"

Weapon::Weapon(unsigned int i_ammo, unsigned i_magazine) : ammo(i_ammo), magazine(i_magazine) {
	texture.loadFromFile("Resources/Images/weapon.png");
	sprite.setTexture(texture);
	fire_t.loadFromFile("Resources/Images/fire.png");
	fire_s.setTexture(fire_t);
	sprite.setScale(sf::Vector2f(15.f, 15.f));
	sprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4));
	fire_s.setScale(sf::Vector2f(15.f, 15.f));
	fire_s.setPosition(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4));
};

void Weapon::fire() {
	if (ammo > 0) {
		ammo--;
		is_fire = true;
	}
	else {
		is_fire = false;
	}
}
void Weapon::draw(sf::RenderWindow& i_window) {

	if (is_fire) {
		i_window.draw(fire_s);
		is_fire = false;
	}
	i_window.draw(sprite);
}