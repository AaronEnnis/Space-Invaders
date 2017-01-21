#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{ 

public:
	float X;
	float Y;
	float width;
	float height;
	float speed;
	sf::RectangleShape shape;

	Enemy();
	void moveLeft();	
	void moveRight();
	void moveDown();
	void speedUp();
}; 
