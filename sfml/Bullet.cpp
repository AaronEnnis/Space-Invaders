#include "Bullet.h"
Bullet::Bullet()
{
	X = 500;
	Y = 500;
	width = 5;
	height = 5;
	speed = 10.0f;
	shoot = true;
}
void Bullet::move(float x, float y)
{
	if (shoot)
	{
		X = x + 17.5;
		Y = y;
	}
	shoot = false;
	if (shoot == false)
	{
		if (Y > -10)  //stops moving off screen
		{
			Y = Y - speed;
		}
	}
	if (Y < 0)
	{
		shoot = true;
	}
}