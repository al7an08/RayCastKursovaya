#pragma once
#include "SFML/Graphics.hpp"
#include <array>
#include "Header.h"


class Menu
{
private:
	std::array<sf::Texture, BUTTON_NUM> Buttons_Texture;

	bool isMenu = 1;
	bool isLevelChanged = false;
	int menuNum;
	int menuMode = 1;
	float SCREEN_RESIZE = 1.f;

	int level_num = 1;

public:
	Menu();
	void DrawMenu(sf::RenderWindow& i_window);
	bool IsOpen();
	void SetIsOpen();
	void Set_mode(int mode);
	float Get_Screen_Resize();
	void Set_Screen_Resize(float a);

	bool IsLevelChanged();

	int Get_Level_Num();

	void set_is_level_changed();
};

