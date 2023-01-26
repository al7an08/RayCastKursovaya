#include "Menu.h"
#include "Header.h"

Menu::Menu() {
	isMenu = 1;
	for (int i = 0; i < BUTTON_NUM; i++) {
		sf::Texture TempTexture;
		TempTexture.loadFromFile("Resources/Textures/Button" + std::to_string(i) + ".png");
		Buttons_Texture[i] = TempTexture;
	}

	menuMode = 0;
}

void Menu::DrawMenu(sf::RenderWindow& i_window) {
	if (menuMode == 0) {
		sf::Sprite menu1(Buttons_Texture[0]), menu2(Buttons_Texture[1]), menu3(Buttons_Texture[2]), about(Buttons_Texture[0]);
		menu1.scale(SCREEN_RESIZE, SCREEN_RESIZE);
		menu2.scale(SCREEN_RESIZE, SCREEN_RESIZE);
		menu3.scale(SCREEN_RESIZE, SCREEN_RESIZE);
		int menuNum = 0;
		menu1.setPosition(-menu1.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5);
		menu2.setPosition(-menu2.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 2 * SCREEN_HEIGHT / 5);
		menu3.setPosition(-menu3.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 5);
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
			menu2.setColor(sf::Color::Blue);
			menuNum = 2;
		}
		if (sf::IntRect(-menu3.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 5, +menu3.getGlobalBounds().width, menu3.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu3.setColor(sf::Color::Blue);
			menuNum = 3;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) { //если нажали первую кнопку, то выходим из меню 
				isMenu = false;
			}
			if (menuNum == 2) {
				menuMode = 2;
				i_window.draw(about);
				i_window.display();
			}
			if (menuNum == 3)
			{
				i_window.close();
				isMenu = false;
			}

		}
		i_window.draw(menu1);
		i_window.draw(menu2);
		i_window.draw(menu3);
		i_window.display();
	}

	if (menuMode == 2) {
		int optionNum = 0;
		sf::Sprite menu1(Buttons_Texture[3]), menu2(Buttons_Texture[4]), menu3(Buttons_Texture[5]), menu4(Buttons_Texture[6]);
		menu1.scale(SCREEN_RESIZE, SCREEN_RESIZE);
		menu2.scale(SCREEN_RESIZE, SCREEN_RESIZE);
		menu3.scale(SCREEN_RESIZE, SCREEN_RESIZE);
		menu4.scale(SCREEN_RESIZE, SCREEN_RESIZE);
		menu1.setPosition(-menu1.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 0);
		menu2.setPosition(-menu2.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 1 * SCREEN_HEIGHT / 4);
		menu3.setPosition(-menu3.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 2 * SCREEN_HEIGHT / 4);
		menu4.setPosition(-menu4.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 4);
		optionNum = 0;
		if (sf::IntRect(-menu2.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 1 * SCREEN_HEIGHT / 4, +menu2.getGlobalBounds().width, menu2.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu2.setColor(sf::Color::Blue);
			optionNum = 1;
		}
		if (sf::IntRect(-menu3.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 2 * SCREEN_HEIGHT / 4, +menu3.getGlobalBounds().width, menu3.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu3.setColor(sf::Color::Blue);
			optionNum = 2;
		}
		if (sf::IntRect(-menu4.getGlobalBounds().width / 2 + SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 4, +menu4.getGlobalBounds().width, menu4.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu4.setColor(sf::Color::Blue);
			optionNum = 3;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (optionNum == 0) {
				
			}
			if (optionNum == 1) 
			{
				i_window.setSize(sf::Vector2u(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
			}
			if (optionNum == 2) {
				i_window.setSize(sf::Vector2u(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5));
			}
			if (optionNum == 3)
			{
				i_window.setSize(sf::Vector2u(SCREEN_WIDTH / 1, SCREEN_HEIGHT / 1));
			}

		}
		i_window.draw(menu1);
		i_window.draw(menu2);
		i_window.draw(menu3);
		i_window.draw(menu4);
		i_window.display();
	}
}


bool Menu::IsOpen() {
	return isMenu;
}

void Menu::SetIsOpen() {
	isMenu = true;
}