#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "Header.h"
#include "MapCollision.h"
#include "Player.h"
#include "ConvertSketch.h"
#include "Menu.h"
#include "SFML/Graphics.hpp"

//#pragma comment(lib, "sfml-graphics.lib")
//#pragma comment(lib, "sfml-window.lib")
//#pragma comment(lib, "sfml-system.lib")


bool draw_map = true;

std::vector<std::vector<Cell>> map{};

int main()
{
	Menu* menu1 = new Menu;
	menu1->Set_Screen_Resize(2.f);
	sf::RenderWindow window_1(sf::VideoMode(960, 540), "Set resolution");

	// run the program as long as the window is open
	while (window_1.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event1;
		while (window_1.pollEvent(event1))
		{
			// "close requested" event: we close the window
			if (event1.type == sf::Event::Closed)
				window_1.close();
		}

		menu1->Set_mode(2);

		menu1->DrawMenu(window_1);


	}

	const float SCREEN_RESIZE = menu1->Get_Screen_Resize();


	//Значение от которого зависит, есть ли миникарта или нет

	//Это переменная нужна, чтобы избавиться от зависимости от количества кадров в секунду
	std::chrono::microseconds lag(0);

	std::chrono::steady_clock::time_point previous_time;
	//Экземпляр класса Event
	sf::Event event;


	sf::RenderWindow window(sf::VideoMode(int(SCREEN_WIDTH / SCREEN_RESIZE), int(SCREEN_HEIGHT / SCREEN_RESIZE)), "RayCaster", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));

	sf::Sprite map_grid_cell_sprite;
	sf::Sprite map_wall_sprite;
	Menu menu;

	unsigned short window_center_x = static_cast<unsigned short>(round(0.5f * window.getSize().x)); // Координаты середины окна
	unsigned short window_center_y = static_cast<unsigned short>(round(0.5f * window.getSize().y));

	sf::Mouse::setPosition(sf::Vector2i(window_center_x, window_center_y), window);

	menu.Set_Screen_Resize(menu1->Get_Screen_Resize());

	delete menu1;

	sf::Texture map_grid_cell_texture;
	map_grid_cell_texture.loadFromFile("Resources/Images/MapGridCell.png");

	std::array<sf::Texture, NUM_WALL_TYPES> map_wall_textures;
	std::array<sf::Sprite, NUM_WALL_TYPES> map_wall_sprites;

	for (int i = 0; i < NUM_WALL_TYPES; i++) {
		sf::Texture temp_texture;
		temp_texture.loadFromFile("Resources/Images/MapWall" + std::to_string(i) + std::to_string(MAP_CELL_SIZE) + ".png");
		map_wall_textures[i] = temp_texture;
		sf::Sprite temp_sprite;
		temp_sprite.setTexture(temp_texture);
		map_wall_sprites[i] = (temp_sprite);
	}

	window.setMouseCursorVisible(false);
	Player player(0, 0, 100);

	std::string level = "Resources/Levels/level_map1.png";
	std::array<std::string, LEVELS_NUM> levels;
	for (int i = 0; i < LEVELS_NUM; i++) {
		levels[i] = ("Resources/Levels/level_map" + std::to_string(i + 1) + ".png");
	}

	map = convert_sketch(player, level);

	int MAP_HEIGHT = map[0].size();
	int MAP_WIDTH = map.size();


	map_grid_cell_sprite.setTexture(map_grid_cell_texture);
	map_grid_cell_sprite.setTextureRect(sf::IntRect(0, 0, MAP_GRID_CELL_SIZE, MAP_GRID_CELL_SIZE));

	previous_time = std::chrono::steady_clock::now();

	while (1 == window.isOpen())
	{
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (1 == window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();

				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
					case sf::Keyboard::M:
					{
						if (draw_map == true) {
							draw_map = false;
						}
						else {
							draw_map = true;
						}
						break;
					}

					case sf::Keyboard::Z:
					{
						window.close();

						break;
					}
					case sf::Keyboard::Escape:
					{
						menu.Set_mode(0);
						menu.SetIsOpen();
						break;
					}
				}
			}
			}
		}

		if (menu.IsOpen()) {
			window.clear(sf::Color(73, 255, 255));
			window.setMouseCursorVisible(true);
			menu.DrawMenu(window);
			if (menu.IsLevelChanged()) {
				std::string level = levels[menu.Get_Level_Num() - 1];
				map = convert_sketch(player, level);
				menu.set_is_level_changed();
				int MAP_HEIGHT = map[0].size();
				int MAP_WIDTH = map.size();
			}
		}
		else {
			int MAP_HEIGHT = map[0].size();
			int MAP_WIDTH = map.size();
			window.setMouseCursorVisible(false);
			while (FRAME_DURATION <= lag)
			{
				lag -= FRAME_DURATION;

				player.update(map, window);

				if (FRAME_DURATION > lag)
				{
					//Меняем цвет окна, рисуя таким образом небо
					window.clear(sf::Color(73, 255, 255));

					player.draw_screen(window, map);

					if (draw_map)
					{
						for (unsigned short a = 0; a < ceil(MAP_CELL_SIZE * MAP_WIDTH / static_cast<float>(MAP_GRID_CELL_SIZE)); a++)
						{
							for (unsigned short b = 0; b < ceil(MAP_CELL_SIZE * MAP_HEIGHT / static_cast<float>(MAP_GRID_CELL_SIZE)); b++)
							{
								map_grid_cell_sprite.setPosition(static_cast<float>(MAP_GRID_CELL_SIZE * a), static_cast<float>(MAP_GRID_CELL_SIZE * b));

								window.draw(map_grid_cell_sprite);
							}
						}

						for (unsigned short a = 0; a < MAP_WIDTH; a++)
						{
							for (unsigned short b = 0; b < MAP_HEIGHT; b++)
							{
								for (int i = 1; i <= NUM_WALL_TYPES; i++) {
									if (i == map[a][b]) {
										sf::Sprite temp_sprite;
										temp_sprite.setTexture(map_wall_textures[i - 1]);
										temp_sprite.setPosition(static_cast<float>(MAP_CELL_SIZE * a), static_cast<float>(MAP_CELL_SIZE * b));
										window.draw(temp_sprite); // Рисование спрайта
									}
								}
							}
						}
						player.draw_map(window);
					}

					window.display();
				}
			}
		}
	}
}