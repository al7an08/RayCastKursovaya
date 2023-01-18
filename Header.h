#pragma once
#include <chrono>

constexpr float FOV_HORIZONTAL = 90;
constexpr float FOV_VERTICAL = 58.75f;
constexpr float MOVEMENT_SPEED = 2;
//����� ��
constexpr float PI = 3.141592653589793116f;
constexpr float RENDER_DISTANCE = 1024;

//�������� �������� �����������
constexpr float ENEMY_ROTATION_SPEED = 2;

//������ ������(������) � ����
constexpr unsigned char CELL_SIZE = 64;
//������ ������ �� ���������
constexpr unsigned char MAP_CELL_SIZE = 8;
constexpr unsigned char MAP_GRID_CELL_SIZE = 16;
constexpr unsigned char MAP_HEIGHT = 24;
constexpr unsigned char MAP_WIDTH = 40;
constexpr unsigned char SCREEN_RESIZE = 1;

constexpr unsigned short SCREEN_HEIGHT = 720;
constexpr unsigned short SCREEN_WIDTH = 1280;

//���� � ��� 60 ������ � 1 �������, �� ������ ���� ����� ������ 16.667 ��
constexpr std::chrono::microseconds FRAME_DURATION(16667);

//���� ������
enum Cell
{
	Empty,
	Wall,
	Wall1
};