#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
	float X;
	float Y;
	float speed;
	float height;
	float width;
	bool alive;
	sf::RectangleShape shape;

	Player();
	void move();
};