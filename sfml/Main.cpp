#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

Bullet bullet[3] = {};
Enemy enemy[20] = {};
Player player;
int playerScore = 0;
int count = 0; //index for which bullet is being used

bool collision(sf::RectangleShape enemyShape, sf::RectangleShape bulletShape, sf::RectangleShape playerShape)
{
	if (enemyShape.getGlobalBounds().intersects(bulletShape.getGlobalBounds()) == true)
	{	
		bullet[count].Y = -10;
		playerScore++;
		return true;
	}
	else if (enemyShape.getGlobalBounds().intersects(playerShape.getGlobalBounds()) == true)
	{
		player.alive = false;
		player.Y = 550;
		for (int i = 0; i < 20; i++)
		{
			enemy[i].Y = -100;
		}
	}
	return false;
}

int main()
{	
	bool pause = false;
	bool shoot = true;
	bool enemyLeft = true;

	float windowWidth = 500;
	float windowHeight = 500;

	for (int i = 1; i < 20; i++)		//sets the starting possition of the enemies
	{
		if(i == 5)
		{
			enemy[i].X = enemy[0].X;
			enemy[i].Y = (enemy[0].Y+50);
		}
		else if (i == 10)
		{
			enemy[i].X = enemy[0].X;
			enemy[i].Y = (enemy[0].Y + 100);
		}
		else if (i == 15)
		{
			enemy[i].X = enemy[0].X;
			enemy[i].Y = (enemy[0].Y + 150);
		}
		else
		{
			enemy[i].X = (enemy[i - 1].X + 50);
			enemy[i].Y = enemy[i - 1].Y;
		}
	}
		
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Space Invaders");
	player.shape = sf::RectangleShape (sf::Vector2f(player.width, player.height));
	for (int i = 0; i < 3; i++)
	{
		bullet[i].shape = sf::RectangleShape(sf::Vector2f(bullet[i].width, bullet[i].height));
	}

	for (int i = 0; i < 20; i++)
	{
		enemy[i].shape = sf::RectangleShape(sf::Vector2f(enemy[i].width, enemy[i].height));
	}

	player.shape.setFillColor(sf::Color::Red);
	player.shape.setPosition(player.X, player.Y);

	for (int i = 0; i < 20; i++)
	{
		enemy[i].shape.setFillColor(sf::Color::Blue);
		enemy[i].shape.setPosition(enemy[i].X, enemy[i].Y);
	}
	for (int i = 0; i < 3; i++)
	{
		bullet[i].shape.setFillColor(sf::Color::Green);
		bullet[i].shape.setPosition(bullet[i].X, bullet[i].Y);
	}

	//setting the text
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text text;
	text.setFont(font); 
	text.setCharacterSize(24); 
	text.setFillColor(sf::Color::Green);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);


	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);		//frame rate
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			if (pause == false)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					pause = true;
				}
			
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					shoot = false;
				}

				if (shoot == false)
				{
					bullet[count].move(player.X, player.Y); //spawns bullet at player
				}
				if (bullet[count].Y == -10)
				{
					shoot = true;
					count++;
					if (count == 3)
					{
						count = 0;
					}
				}
				//enemy movement
				for (int i = 0; i < 20; i++)
				{
					if (enemy[i].X <= 0)
					{
						enemyLeft = false;
						for (int j = 0; j < 20; j++)
						{
							enemy[j].moveDown();	
						}
						break;
					}
					if ((enemy[i].X + enemy[i].width) >= 500)
					{
						enemyLeft = true;
						for (int j = 0; j < 20; j++)
						{
							enemy[j].moveDown();							
						}
						break;
					}
				}

				for (int i = 0; i < 20; i++)
				{
					if (enemyLeft == true)
					{
						enemy[i].moveLeft();
					}
					else
					{
						enemy[i].moveRight();
					}
				}

				//functions being called
				for (int i = 0; i < 20; i++)
				{
					if(collision(enemy[i].shape, bullet[count].shape, player.shape))
					{
						enemy[i].Y = -100;
						shoot = true;
						if (playerScore == 10)
						{
							for (int i = 0; i < 20; i++)
							{
								enemy[i].speedUp();
							}
						}
						if (playerScore == 17)
						{
							for (int i = 0; i < 20; i++)
							{
								enemy[i].speedUp();
							}
						}
					}
				}

				for (int i = 0; i < 20; i++)
				{
					if ((enemy[i].Y + 40) > 440)		//stops the player moving when enemy on the same Y axis
					{
						player.alive = false;
					}
				}

				player.move();	
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))			//un-pause
			{
				pause = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				pause = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				pause = false;
			}

			player.shape.setPosition(player.X, player.Y);
			bullet[count].shape.setPosition(bullet[count].X, bullet[count].Y);
			for (int i = 0; i < 20; i++)
			{
				enemy[i].shape.setPosition(enemy[i].X, enemy[i].Y);
			}

			if (player.alive == false && playerScore < 20)		//selects which text to display
			{
				text.setPosition(175, 200);
				text.setString("You are dead");
			}
			if (playerScore == 20)
			{
				text.setPosition(200, 200);
				text.setString("You win");
				player.alive = false;
			}

			window.clear();
			
			window.draw(bullet[count].shape);
			window.draw(player.shape);
			for (int i = 0; i < 20; i++)
			{
				window.draw(enemy[i].shape);
			}
			window.draw(text);
			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
	return 0;
}