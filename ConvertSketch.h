#pragma once

#include "Header.h"
#include "Player.h"
#include <iostream>

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(Player& i_player);

