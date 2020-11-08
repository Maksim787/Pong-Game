#include <SFML\Graphics.hpp>
#include "Rocket.h"
#include "Ball.h"
#include <ctime>
#include <iostream>

float screenX = 1200;
float screenY = 800;

int main()
{
	srand(time(0));
	// Player's size and speed
	sf::Vector2f player_size(15, screenY / 4);
	float player_speed = 1100;

	// Ball's radius and speed
	float ballRadius = 15;
	float ballVelocity = 1000;

	// Pause
	bool pause = true;
	bool gameRestart = true;

	// Score
	sf::Font font;
	font.loadFromFile("DigitalDisplayRegular-ODEO.ttf");

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(screenX / 9);
	text.setOrigin(static_cast<float>(text.getCharacterSize()) / 4, 0);

	sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Pong");

	// Closk
	sf::Clock clock;
	float deltaTime;

	while (gameRestart && window.isOpen())
	{
		gameRestart = false;
		pause = true;

		// Players
		Rocket player1(true, player_speed);
		Rocket player2(false, player_speed);

		// Ball
		Ball ball(ballRadius, ballVelocity);

		// First Position
		window.clear();
		player1.Draw(window);
		player2.Draw(window);
		ball.Draw(window);
		player1.DrawScore(window, text);
		player2.DrawScore(window, text);
		window.display();

		while (window.isOpen() && !gameRestart)
		{

			sf::Event e;
			while (window.pollEvent(e))
			{
				// Close Window (Closed)
				if (e.type == sf::Event::Closed)
					window.close();
				if (e.type == sf::Event::KeyPressed)
				{
					// Pause (Space)
					if (e.key.code == sf::Keyboard::Space)
						pause = !pause;
					// Close Window (Esc)
					else if (e.key.code == sf::Keyboard::Escape)
						window.close();
					// Restart Game (R)
					else if (e.key.code == sf::Keyboard::R)
						gameRestart = true;
				}
				if (e.type == sf::Event::Resized)
				{
					screenX = window.getSize().x;
					screenY = window.getSize().y;
					player1.SetStartPosition();
					player2.SetStartPosition();
					ball.SetStartPosition();
				}
			}

			// Timer
			if (!pause)
				deltaTime = clock.getElapsedTime().asSeconds();
			clock.restart();

			if (!pause)
			{
				// Player 1
				// Move Up (W, A)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					player1.Update(-1, deltaTime);
				// Move Down (S, D)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					player1.Update(1, deltaTime);

				// Player 2
				// Move Up (I, L)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
					player2.Update(-1, deltaTime);
				// Move Down (K, J)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::J))
					player2.Update(1, deltaTime);

				window.clear();

				// Updating ball
				ball.Update(player1, player2, deltaTime, pause);

				player1.Draw(window);
				player2.Draw(window);

				player1.DrawScore(window, text);
				player2.DrawScore(window, text);

				ball.Draw(window);

				window.display();
			}

		}

	}

	return 0;
}