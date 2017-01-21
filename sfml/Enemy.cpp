#include "Enemy.h"

Enemy::Enemy()
{
	X = 40;
	Y = 9;
	width = 40;
	height = 40;
	speed = 2;
}

void Enemy::moveLeft()
{
	if (Y > 0) //stops moving off screen
	{	
		X = X - speed;	
	}	
}
void Enemy::moveRight()
{
	if (Y > 0) 
	{
		X = X + speed;
	}
}
void Enemy::moveDown()
{
	if (Y > 0)
	{
		Y = Y + 40;
	}
}
void Enemy::speedUp()
{
	speed = speed + 1.5;
}
