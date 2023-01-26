#include "Menu.h"
#include "Header.h"

Menu::Menu() {
	isMenu = 1;
	Texture_Button1.loadFromFile("Resources/Textures/Button1.png");
	Texture_Button2.loadFromFile("Resources/Textures/Button1.png");
	Texture_Button3.loadFromFile("Resources/Textures/Button1.png");
}

void Menu::DrawMenu(sf::RenderWindow& i_window) {
	sf::Sprite menu1(Texture_Button1), menu2(Texture_Button1), menu3(Texture_Button1), about(Texture_Button1);
	menu1.scale(5.f, 5.f);
	menu2.scale(5.f, 5.f);
	menu3.scale(5.f, 5.f);
	int menuNum = 0;
	menu1.setPosition(- menu1.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5);
	menu2.setPosition(- menu2.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 2 * SCREEN_HEIGHT / 5);
	menu3.setPosition(- menu3.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 5);
	menu1.setColor(sf::Color::White);
	menu2.setColor(sf::Color::White);
	menu3.setColor(sf::Color::White);
	menuNum = 0;
	i_window.clear(sf::Color(129, 181, 221));
	

	if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(i_window))) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
	if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(i_window))) { menu2.setColor(sf:: Color::Blue); menuNum = 2; }
	if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(i_window))) { menu3.setColor(sf::Color::Blue); menuNum = 3; }

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
		if (menuNum == 2) { i_window.draw(about); i_window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
		if (menuNum == 3) { i_window.close(); isMenu = false; }

	}
	i_window.draw(menu1);
	i_window.draw(menu2);
	i_window.draw(menu3);
	i_window.display();
}

bool Menu::IsOpen() {
	return isMenu;
}

void Menu::SetIsOpen() {
	isMenu = true;
}