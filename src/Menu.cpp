#include "Menu.h"
#include "Header.h"

Menu::Menu() {
	isMenu = 1;
	Texture_Button1.loadFromFile("Resources/Textures/Button1.png");
	Texture_Button2.loadFromFile("Resources/Textures/Button2.png");
	Texture_Button3.loadFromFile("Resources/Textures/Button3.png");
}

void Menu::DrawMenu(sf::RenderWindow& i_window) {
	sf::Sprite menu1(Texture_Button1), menu2(Texture_Button2), menu3(Texture_Button3), about(Texture_Button1);
	menu1.scale(SCREEN_RESIZE, SCREEN_RESIZE);
	menu2.scale(SCREEN_RESIZE, SCREEN_RESIZE);
	menu3.scale(SCREEN_RESIZE, SCREEN_RESIZE);
	int menuNum = 0;
	menu1.setPosition(- menu1.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5);
	menu2.setPosition(- menu2.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 2 * SCREEN_HEIGHT / 5);
	menu3.setPosition(- menu3.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 5);
	menu1.setColor(sf::Color::White);
	menu2.setColor(sf::Color::White);
	menu3.setColor(sf::Color::White);
	
	i_window.clear(sf::Color(129, 181, 221));
	

	if (sf::IntRect(-menu1.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5, +menu1.getGlobalBounds().width, menu1.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
	{ 
		menu1.setColor(sf::Color::Blue); 
		menuNum = 1; 
	}
	if (sf::IntRect(-menu2.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 2 * SCREEN_HEIGHT / 5, +menu2.getGlobalBounds().width, menu2.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
	{ 
		menu2.setColor(sf:: Color::Blue); 
		menuNum = 2; 
	}
	if (sf::IntRect(-menu3.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 5, +menu3.getGlobalBounds().width, menu3.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
	{ 
		menu3.setColor(sf::Color::Blue); 
		menuNum = 3; 
	}

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