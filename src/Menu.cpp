#include "Menu.h"
#include "Header.h"
#include <math.h>
Menu::Menu() {
	isMenu = 1;
	for (int i = 0; i < BUTTON_NUM; i++) {
		sf::Texture* TempTexture = new sf::Texture();
		TempTexture->loadFromFile("Resources/Textures/Button" + std::to_string(i) + ".png");
		Buttons_Texture[i] = *TempTexture;
		delete TempTexture;
	}
	menuNum = 0;
	menuMode = 0;
}

void Menu::DrawMenu(sf::RenderWindow& i_window) {
	int optionNum = 0;
	int levelNum = 0;
	if (menuMode == 0) {
		sf::Sprite menu1(Buttons_Texture[0]), menu2(Buttons_Texture[1]), menu3(Buttons_Texture[2]), about(Buttons_Texture[0]);
		float WIDTH = SCREEN_WIDTH / SCREEN_RESIZE;
		float HEIGHT = SCREEN_HEIGHT / SCREEN_RESIZE;

		menu1.scale(1 / sqrt(SCREEN_RESIZE), 1 / sqrt(SCREEN_RESIZE));
		menu2.scale(1 / sqrt(SCREEN_RESIZE), 1 / sqrt(SCREEN_RESIZE));
		menu3.scale(1 / sqrt(SCREEN_RESIZE), 1 / sqrt(SCREEN_RESIZE));

		menu1.setColor(sf::Color::White);
		menu2.setColor(sf::Color::White);
		menu3.setColor(sf::Color::White);

		i_window.clear(sf::Color(129, 181, 221));

		menu1.setPosition(sf::Vector2f((-menu1.getGlobalBounds().width / 2) + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 5));
		menu2.setPosition(sf::Vector2f((-menu2.getGlobalBounds().width / 2) + (SCREEN_WIDTH / 2), 2 * SCREEN_HEIGHT / 5));
		menu3.setPosition(sf::Vector2f((-menu3.getGlobalBounds().width / 2) + (SCREEN_WIDTH / 2), 3 * SCREEN_HEIGHT / 5));

		if (sf::IntRect(int(-menu1.getGlobalBounds().width / 2 + WIDTH / 2), int(HEIGHT / 5), +menu1.getGlobalBounds().width, menu1.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu1.setColor(sf::Color::Blue);
			menuNum = 1;
		}
		else if (sf::IntRect(int(-menu2.getGlobalBounds().width / 2 + WIDTH / 2), int(2 * HEIGHT / 5), +menu2.getGlobalBounds().width, menu2.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu2.setColor(sf::Color::Blue);
			menuNum = 2;
		}
		else if (sf::IntRect(int(-menu3.getGlobalBounds().width / 2 + WIDTH / 2), int(3 * HEIGHT / 5), +menu3.getGlobalBounds().width, menu3.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu3.setColor(sf::Color::Blue);
			menuNum = 3;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) { //если нажали первую кнопку, то выходим из меню 
				isMenu = false;
			}
			else if (menuNum == 2) {
				menuMode = 3;
			}
			else if (menuNum == 3)
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
		sf::Sprite menu1(Buttons_Texture[3]), menu2(Buttons_Texture[4]), menu3(Buttons_Texture[5]), menu4(Buttons_Texture[6]);
		menu1.scale(1 / (SCREEN_RESIZE), 1 / (SCREEN_RESIZE));
		menu2.scale(1 / (SCREEN_RESIZE), 1 / (SCREEN_RESIZE));
		menu3.scale(1 / (SCREEN_RESIZE), 1 / (SCREEN_RESIZE));
		menu4.scale(1 / (SCREEN_RESIZE), 1 / (SCREEN_RESIZE));

		float WIDTH = SCREEN_WIDTH / SCREEN_RESIZE;
		float HEIGHT = SCREEN_HEIGHT / SCREEN_RESIZE;

		menu1.setPosition(-menu1.getGlobalBounds().width / 2 + (WIDTH) / 2, 0);
		menu2.setPosition(-menu2.getGlobalBounds().width / 2 + (WIDTH) / 2, 1 * (HEIGHT) / 4);
		menu3.setPosition(-menu3.getGlobalBounds().width / 2 + (WIDTH) / 2, 2 * (HEIGHT) / 4);
		menu4.setPosition(-menu4.getGlobalBounds().width / 2 + (WIDTH) / 2, 3 * (HEIGHT) / 4);

		i_window.clear(sf::Color(129, 181, 221));

		if (sf::IntRect(-menu2.getGlobalBounds().width / 2 + (WIDTH) / 2, 1 * (HEIGHT) / 4 , +menu2.getGlobalBounds().width, menu2.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu2.setColor(sf::Color::Blue);
			optionNum = 1;
		}
		else if (sf::IntRect(-menu3.getGlobalBounds().width / 2 + (WIDTH) / 2, 2 * (HEIGHT) / 4, +menu3.getGlobalBounds().width, menu3.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu3.setColor(sf::Color::Blue);
			optionNum = 2;
		}
		else if (sf::IntRect(-menu4.getGlobalBounds().width / 2 + (WIDTH) / 2, 3 * (HEIGHT) / 4, +menu4.getGlobalBounds().width, menu4.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu4.setColor(sf::Color::Blue);
			optionNum = 3;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (optionNum == 1) { //если нажали первую кнопку, то выходим из меню 
				SCREEN_RESIZE = 2;
				i_window.close();
			}
			else if (optionNum == 2) {
				SCREEN_RESIZE = 1.5f;
				i_window.close();
			}
			else if (optionNum == 3)
			{
				SCREEN_RESIZE = 1;
				i_window.close();
			}

		}
		i_window.draw(menu1);
		i_window.draw(menu2);
		i_window.draw(menu3);
		i_window.draw(menu4);
		i_window.display();
	}

	if (menuMode == 3) {
		sf::Sprite menu1(Buttons_Texture[7]), menu2(Buttons_Texture[8]), menu3(Buttons_Texture[9]), menu4(Buttons_Texture[10]);
		menu1.scale(1 / (SCREEN_RESIZE), 1 / (SCREEN_RESIZE));
		menu2.scale(1 / (SCREEN_RESIZE), 1 / (SCREEN_RESIZE));
		menu3.scale(1 / (SCREEN_RESIZE), 1 / (SCREEN_RESIZE));
		menu4.scale(1 / (SCREEN_RESIZE), 1 / (SCREEN_RESIZE));

		menu1.setPosition(-menu1.getGlobalBounds().width / 2 + (SCREEN_WIDTH ) / 2, 0);
		menu2.setPosition(-menu2.getGlobalBounds().width / 2 + (SCREEN_WIDTH ) / 2, 1 * (SCREEN_HEIGHT ) / 4);
		menu3.setPosition(-menu3.getGlobalBounds().width / 2 + (SCREEN_WIDTH ) / 2, 2 * (SCREEN_HEIGHT ) / 4);
		menu4.setPosition(-menu4.getGlobalBounds().width / 2 + (SCREEN_WIDTH ) / 2, 3 * (SCREEN_HEIGHT ) / 4);

		if (sf::IntRect(-menu2.getGlobalBounds().width / 2 + (SCREEN_WIDTH / SCREEN_RESIZE) / 2, 1 * (SCREEN_HEIGHT / SCREEN_RESIZE) / 4, +menu2.getGlobalBounds().width, menu2.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu2.setColor(sf::Color::Blue);
			levelNum = 1;
		}
		else if (sf::IntRect(-menu3.getGlobalBounds().width / 2 + (SCREEN_WIDTH / SCREEN_RESIZE) / 2, 2 * (SCREEN_HEIGHT / SCREEN_RESIZE) / 4, +menu3.getGlobalBounds().width, menu3.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu3.setColor(sf::Color::Blue);
			levelNum = 2;
		}
		else if (sf::IntRect(-menu4.getGlobalBounds().width / 2 + (SCREEN_WIDTH / SCREEN_RESIZE) / 2, 3 * (SCREEN_HEIGHT / SCREEN_RESIZE) / 4, +menu4.getGlobalBounds().width, menu4.getGlobalBounds().height).contains(sf::Mouse::getPosition(i_window)))
		{
			menu4.setColor(sf::Color::Blue);
			levelNum = 3;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (levelNum == 1) { //если нажали первую кнопку, то выходим из меню 
				if (level_num != 1) {
					level_num = 1;
					isLevelChanged = true;
				}
				isMenu = false;
			}
			else if (levelNum == 2) {
				if (level_num != 2) {
					level_num = 2;
					isLevelChanged = true;
				}
				isMenu = false;
			}
			else if (levelNum == 3)
			{
				if (level_num != 3) {
					level_num = 3;
					isLevelChanged = true;
				}
				isMenu = false;
			}

		}
		i_window.draw(menu1);
		i_window.draw(menu2);
		i_window.draw(menu3);
		i_window.draw(menu4);
		i_window.display();
	}
}

void Menu::Set_mode(int mode) {
	menuMode = mode;
}
bool Menu::IsOpen() {
	return isMenu;
}

void Menu::SetIsOpen() {
	isMenu = true;
}

float Menu::Get_Screen_Resize() {
	return SCREEN_RESIZE;
}

void Menu::Set_Screen_Resize(float a) {
	SCREEN_RESIZE = a;
}

bool Menu::IsLevelChanged() {
	return isLevelChanged;
}

int Menu::Get_Level_Num() {
	return level_num;
}

void Menu::set_is_level_changed() {
	isLevelChanged = false;
}