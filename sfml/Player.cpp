#include "Player.h"

Player::Player()
{
	X = 100;
	Y = 440;
	width = 40;
	height = 40;
	speed = 5.0f;
	alive = true;
}
void Player::move()
{
	if (alive)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			X = X - speed;
			if ((X + 40) < 0)
			{
				X = 495;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			X = X + speed;
			if (X == 500)
			{
				X = -35;
			}
		}
	}
}