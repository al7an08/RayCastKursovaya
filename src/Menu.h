#pragma once
#include "SFML/Graphics.hpp"


class Menu
{
private:
	sf::Texture Texture_Button1, Texture_Button2, Texture_Button3;
	sf::Sprite Sprite_Button1, Sprite_Button2, Sprite_Button3;
	bool isMenu = 1;
	int menuNum;
	int menuMode;
public:
	Menu();
	void DrawMenu(sf::RenderWindow& i_window);
	bool IsOpen();
	void SetIsOpen();
};

