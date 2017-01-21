#pragma once
#include <SFML/Graphics.hpp>
class Bullet {
public:
	float X;
	float Y;
	float width;
	float height;
	float speed;
	bool shoot;
	sf::RectangleShape shape;

	Bullet();
	void move(float x, float y);
};
