#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Boundary
{
private:
	sf::VertexArray vertexarray;
public:
	Boundary(int x1, int y1, int x2, int y2);
	void Show(sf::RenderWindow& i_window);
};

