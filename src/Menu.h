#pragma once
#include "SFML/Graphics.hpp"
#include <array>
#include "Header.h"


class Menu
{
private:
	std::array<sf::Texture, BUTTON_NUM> Buttons_Texture;
	bool isMenu = 1;
	int menuNum;
	int menuMode;
public:
	Menu();
	void DrawMenu(sf::RenderWindow& i_window);
	bool IsOpen();
	void SetIsOpen();
};

