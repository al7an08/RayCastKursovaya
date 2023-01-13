#include "Boundary.h"
#include "SFML/Graphics.hpp"


Boundary::Boundary(int x1, int y1, int x2, int y2) {
	sf::VertexArray a(sf::Lines, 2);
	a[0].position = sf::Vector2f(x1, y1);
	a[1].position = sf::Vector2f(x2, y2);
	this->vertexarray = a;
}

void Boundary::Show(sf::RenderWindow& i_window) {
	i_window.draw(vertexarray);
}