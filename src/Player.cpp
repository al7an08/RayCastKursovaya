#include <array>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Header.h"
#include "Player.h"
#include "MapCollision.h"
#include "GetDegrees.h"
#include "RadToDeg.h"
#include <iostream>

Player::Player(float i_x, float i_y, float i_hp) : // Конструктор класса Player
	direction_horizontal(0),
	direction_vertical(0),
	x(i_x),
	y(i_y),
	hp(i_hp),
	map_player_sprite(map_player_texture)

{
	map_player_texture.loadFromFile("Resources/Images/MapPlayer" + std::to_string(MAP_CELL_SIZE) + ".png"); // Загрузка текстуры из файла

	for (int i = 0; i < NUM_WALL_TYPES; i++) {
		sf::Texture temp_texture;
		temp_texture.loadFromFile("Resources/Images/Wall" + std::to_string(i) + std::to_string(CELL_SIZE) + ".png");
		wall_textures[i] = temp_texture;
		sf::Sprite temp_sprite;
		temp_sprite.setTexture(temp_texture);
		wall_sprites[i] = (temp_sprite);
	}
	
	enemy_texture.loadFromFile("Resources/Images/Steven" + std::to_string(CELL_SIZE) + ".png");
	enemy_sprite.setTexture(enemy_texture);
}

void Player::draw_map(sf::RenderWindow& i_window) // отрисовка миникарты
{
	//Определяем направление взгляда игрока
	float frame_angle = 360.f * MAP_CELL_SIZE / map_player_texture.getSize().x;
	
	float shifted_direction = get_degrees(direction_horizontal + 0.5f * frame_angle);
	float start_x = x + 0.5f * CELL_SIZE;
	float start_y = y + 0.5f * CELL_SIZE;

	//Визуализация угла обзора
	//Каждая из точек, в которой один из лучей пересекает какой-либо объект, является вершиной выпуклого многоугольника sf::TriangleFan 
	sf::VertexArray fov_visualization(sf::TriangleFan, 1 + SCREEN_WIDTH);
	
	fov_visualization[0].position = sf::Vector2f(MAP_CELL_SIZE * start_x / CELL_SIZE, MAP_CELL_SIZE * start_y / CELL_SIZE);

	map_player_sprite.setPosition(round(MAP_CELL_SIZE * x / CELL_SIZE), round(MAP_CELL_SIZE * y / CELL_SIZE));
	map_player_sprite.setTextureRect(sf::IntRect(static_cast<unsigned short>(MAP_CELL_SIZE * floor(shifted_direction / frame_angle)), 0, MAP_CELL_SIZE, MAP_CELL_SIZE));

	for (unsigned short a = 0; a < SCREEN_WIDTH; a++)
	{
		float ray_direction = get_degrees(direction_horizontal + FOV_HORIZONTAL * (floor(0.5f * SCREEN_WIDTH) - 1 - a) / (SCREEN_WIDTH - 1));

		// Находим точку, в которую упирается луч
		fov_visualization[1 + a].position = sf::Vector2f(MAP_CELL_SIZE * (start_x + view_rays[a] * cos(deg_to_rad(ray_direction))) / CELL_SIZE, MAP_CELL_SIZE * (start_y - view_rays[a] * sin(deg_to_rad(ray_direction))) / CELL_SIZE);
	}

	i_window.draw(fov_visualization);
	i_window.draw(map_player_sprite);
}

void Player::draw_screen(sf::RenderWindow& i_window, std::vector<std::vector<Cell>>& i_map)
{
	int MAP_HEIGHT = i_map[0].size();
	int MAP_WIDTH = i_map.size();

	bool draw_enemies = 0;
	//Это расстояние, когда высота проекции и высота стены перед игроком равны
	float projection_distance = 0.5f * CELL_SIZE / tan(deg_to_rad(0.5f * FOV_VERTICAL));
	
	float floor_level = round(0.5f * SCREEN_HEIGHT * (1 + tan(deg_to_rad(direction_vertical)) / tan(deg_to_rad(0.5f * FOV_VERTICAL))));
	float ray_start_x = x + 0.5f * CELL_SIZE;
	float ray_start_y = y + 0.5f * CELL_SIZE;

	

	short previous_column = SHRT_MIN;

	sf::RectangleShape floor_shape(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT - floor_level));
	floor_shape.setFillColor(sf::Color(36, 219, 0));
	floor_shape.setPosition(0, floor_level);

	


	i_window.draw(floor_shape);

	for (unsigned short rays = 0; rays < SCREEN_WIDTH; rays++)
	{
		char cell_step_x = 0;
		char cell_step_y = 0;

		float ray_direction = get_degrees(direction_horizontal + FOV_HORIZONTAL * (floor(0.5f * SCREEN_WIDTH) - rays) / (SCREEN_WIDTH - 1));
		float ray_direction_x = cos(deg_to_rad(ray_direction));
		float ray_direction_y = -sin(deg_to_rad(ray_direction));

		float ray_length = 0;
		float ray_start_x = x + 0.5f * CELL_SIZE;
		float ray_start_y = y + 0.5f * CELL_SIZE;
		// этот луч проверяет на коллизию по горизонтали
		float x_ray_length = 0;
		//Этот луч проверяет на коллизию по вертикали
		float y_ray_length = 0;
		//Длина луча, который движется по одному юниту по координате X
		float x_ray_unit_length = static_cast<float>(CELL_SIZE * sqrt(1 + pow(ray_direction_y / ray_direction_x, 2)));
		//Длина луча, который движется по одному юниту по координате Y
		float y_ray_unit_length = static_cast<float>(CELL_SIZE * sqrt(1 + pow(ray_direction_x / ray_direction_y, 2)));

		unsigned char current_cell_x = static_cast<unsigned char>(floor(ray_start_x / CELL_SIZE));
		unsigned char current_cell_y = static_cast<unsigned char>(floor(ray_start_y / CELL_SIZE));

		if (0 > ray_direction_x)
		{
			cell_step_x = -1;

			x_ray_length = x_ray_unit_length * (ray_start_x / CELL_SIZE - current_cell_x);
		}
		else if (0 < ray_direction_x)
		{
			cell_step_x = 1;

			x_ray_length = x_ray_unit_length * (1 + current_cell_x - ray_start_x / CELL_SIZE);
		}
		else
		{
			cell_step_x = 0;
		}

		if (0 > ray_direction_y)
		{
			cell_step_y = -1;

			y_ray_length = y_ray_unit_length * (ray_start_y / CELL_SIZE - current_cell_y);
		}
		else if (0 < ray_direction_y)
		{
			cell_step_y = 1;

			y_ray_length = y_ray_unit_length * (1 + current_cell_y - ray_start_y / CELL_SIZE);
		}
		else
		{
			cell_step_y = 0;
		}

		// Пока длина луча не превысит дистанцию рендера
		while (RENDER_DISTANCE >= ray_length)
		{
			//На случай если луч попадет в угол
			bool corner_collision = 0;

			//Увеличивание самого короткого из лучей
			if (x_ray_length < y_ray_length)
			{
				ray_length = x_ray_length;
				x_ray_length += x_ray_unit_length;

				current_cell_x += cell_step_x;
			}
			else if (x_ray_length > y_ray_length)
			{
				ray_length = y_ray_length;
				y_ray_length += y_ray_unit_length;

				current_cell_y += cell_step_y;
			}
			else
			{
				//Если лучи одинаковые по длине, что значит, что попали в угол, увеличание длины луча по x и y
				corner_collision = 1;

				ray_length = x_ray_length;
				x_ray_length += x_ray_unit_length;
				y_ray_length += y_ray_unit_length;

				current_cell_x += cell_step_x;
				current_cell_y += cell_step_y;
			}

			//Проверка в пределах ли карты ячейка
			if (0 <= current_cell_x && 0 <= current_cell_y && MAP_HEIGHT > current_cell_y && MAP_WIDTH > current_cell_x)
			{
				if (Cell::Empty != i_map[current_cell_x][current_cell_y])
				{
					//При попадании в какой-то объект остановка бросания лучей
					break;
				}
				else if (1 == corner_collision)
				{
					//Луч не может пройти через 2 стены стоящие диоганально
					if (Cell::Empty != i_map[current_cell_x - cell_step_x][current_cell_y] && Cell::Empty != i_map[current_cell_x][current_cell_y - cell_step_y])
					{
						break;
					}
				}
			}
		}

		//Длина луча должна быть меньше, чем допустимая дистанция рендера
		ray_length = std::min(RENDER_DISTANCE, ray_length);

		view_rays[rays] = ray_length; // сохрянение значения длины луча

		ray_direction = FOV_HORIZONTAL * (floor(0.5f * SCREEN_WIDTH) - rays) / (SCREEN_WIDTH - 1);
		//Пересечение между лучом и проекцией
		float ray_projection_position = 0.5f * tan(deg_to_rad(ray_direction)) / tan(deg_to_rad(0.5f * FOV_HORIZONTAL));

		//Положение текущей колонны на экране
		short current_column = static_cast<short>(round(SCREEN_WIDTH * (0.5f - ray_projection_position)));
		short next_column = SCREEN_WIDTH;

		if (rays < SCREEN_WIDTH - 1)
		{
			float next_ray_direction = FOV_HORIZONTAL * (floor(0.5f * SCREEN_WIDTH) - 1 - rays) / (SCREEN_WIDTH - 1);

			ray_projection_position = 0.5f * tan(deg_to_rad(next_ray_direction)) / tan(deg_to_rad(0.5f * FOV_HORIZONTAL));

			next_column = static_cast<short>(round(SCREEN_WIDTH * (0.5f - ray_projection_position)));
		}

		//Это предотвратит от рисования одной коллоны поверх другой
		if (previous_column < current_column)
		{
			float ray_end_x = ray_start_x + view_rays[rays] * cos(deg_to_rad(get_degrees(direction_horizontal + ray_direction)));
			float ray_end_y = ray_start_y - view_rays[rays] * sin(deg_to_rad(get_degrees(direction_horizontal + ray_direction)));
			//Позиция текстуры стены, которую необходимо нарисовать
			float wall_texture_column_x = 0;

			//Эффект тумана не будет появляться если объект ближе RENDER_DISTANCE / 2
			unsigned char brightness = static_cast<unsigned char>(round(255 * std::max<float>(0, 2 * view_rays[rays] / RENDER_DISTANCE - 1)));

			//Высота коллоны, умноженная на косинус чтобы предотвратить эффект рыбьего глаза
			unsigned short column_height = static_cast<unsigned short>(SCREEN_HEIGHT * projection_distance / (view_rays[rays] * cos(deg_to_rad(ray_direction))));

			//Цвет "тумана" такой же как у неба
			sf::RectangleShape shape(sf::Vector2f(std::max(1, next_column - current_column), column_height));
			shape.setFillColor(sf::Color(73, 255, 255, brightness));
			shape.setPosition(current_column, round(floor_level - 0.5f * column_height));

			previous_column = current_column;

			//Проверяем в какую часть стены коснулся луч, в вертикальную или горизонтальную
			if (abs(ray_end_x - CELL_SIZE * round(ray_end_x / CELL_SIZE)) < abs(ray_end_y - CELL_SIZE * round(ray_end_y / CELL_SIZE)))
			{
				wall_texture_column_x = ray_end_y - CELL_SIZE * floor(ray_end_y / CELL_SIZE);
			}
			else
			{
				wall_texture_column_x = CELL_SIZE * ceil(ray_end_x / CELL_SIZE) - ray_end_x;
			}

			for (int i = 1; i <= NUM_WALL_TYPES; i++) {
				if (i == i_map[current_cell_x][current_cell_y]) {
					sf::Sprite temp_sprite;
					temp_sprite.setTexture(wall_textures[i - 1]);
					temp_sprite.setPosition(current_column, round(floor_level - 0.5f * column_height)); // Указание координат для отрисовки спрайта
					temp_sprite.setTextureRect(sf::IntRect(static_cast<unsigned short>(round(wall_texture_column_x)), 0, 1, CELL_SIZE)); // Текстурирование спрайта
					temp_sprite.setScale(std::max(1, next_column - current_column), column_height / static_cast<float>(CELL_SIZE)); // Scale спрайта
					i_window.draw(temp_sprite); // Рисование спрайта
				}
			}
			i_window.draw(shape);// Рисования "тумана"
		}

	}
}

void Player::set_position(float i_x, float i_y) // Метод выставляющий координаты игрока
{
	x = i_x;
	y = i_y;
}

void Player::update(std::vector<std::vector<Cell>>& i_map, const sf::RenderWindow& i_window)
{
	//Поворот по вертикали и горизонтали
	float rotation_horizontal = 0;
	float rotation_vertical = 0;
	//Изменение координат игрока с последнего обновления
	float step_x = 0;
	float step_y = 0;

	// абсолютные центра координаты окна
	unsigned short window_center_x = static_cast<unsigned short>(round(0.5f * i_window.getSize().x));
	unsigned short window_center_y = static_cast<unsigned short>(round(0.5f * i_window.getSize().y));

	//Управление камеры с помощью мыши
	rotation_horizontal = FOV_HORIZONTAL * (window_center_x - sf::Mouse::getPosition(i_window).x) / i_window.getSize().x;
	rotation_vertical = FOV_VERTICAL * (window_center_y - sf::Mouse::getPosition(i_window).y) / i_window.getSize().y;

	direction_horizontal = get_degrees(direction_horizontal + rotation_horizontal);
	//направление взгляда по вертикали
	direction_vertical = std::max(-89.f, std::min(direction_vertical + rotation_vertical, 89.f)); 

	//Чтобы управление мышью работало, даже если мышь будет выходить из окна
	sf::Mouse::setPosition(sf::Vector2i(window_center_x, window_center_y), i_window);

	//Управление игроком с помощью клавиатуры
	//При нажатии определенной клавиши определяется шаг на который должен сдвинуться игрок по сравнению с последним обновлением
	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		step_x = MOVEMENT_SPEED * cos(deg_to_rad(get_degrees(90 + direction_horizontal)));
		step_y = -MOVEMENT_SPEED * sin(deg_to_rad(get_degrees(90 + direction_horizontal)));
	}
	else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		step_x = MOVEMENT_SPEED * cos(deg_to_rad(get_degrees(direction_horizontal - 90)));
		step_y = -MOVEMENT_SPEED * sin(deg_to_rad(get_degrees(direction_horizontal - 90)));
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		step_x -= MOVEMENT_SPEED * cos(deg_to_rad(direction_horizontal));
		step_y += MOVEMENT_SPEED * sin(deg_to_rad(direction_horizontal));
	}
	else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		step_x += MOVEMENT_SPEED * cos(deg_to_rad(direction_horizontal));
		step_y -= MOVEMENT_SPEED * sin(deg_to_rad(direction_horizontal));
	}

	// Выстрел из выбранного оружия
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		/*gun.fire();*/
	}

	//Проверка на коллизию
	if (0 == map_collision(step_x + x, step_y + y, i_map))
	{
		x += step_x;
		y += step_y;
	}
	else if (0 == map_collision(step_x + x, y, i_map))
	{
		x += step_x;
		y = CELL_SIZE * round(y / CELL_SIZE);
	}
	else if (0 == map_collision(x, step_y + y, i_map))
	{
		x = CELL_SIZE * round(x / CELL_SIZE);
		y += step_y;
	}
	else
	{
		//Располагаем игрока на ближайшей ячейке, чтобы он её касался
		x = CELL_SIZE * round(x / CELL_SIZE);
		y = CELL_SIZE * round(y / CELL_SIZE);
	}
}