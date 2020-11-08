#pragma once
#include <SFML\Graphics.hpp>
#include "Rocket.h"

extern float screenX;
extern float screenY;

class Ball
{
public:
	Ball(float radius, float velocity);
	void CheckCollision(Rocket& player1, Rocket& player2, bool& pause);
	void Update(Rocket& player1, Rocket& player2, float deltaTime, bool& pause);
	void Draw(sf::RenderWindow& window);
	void SetStartPosition();

private:
	sf::CircleShape body;
	sf::Vector2f velocity;
	float ballVelocity;
};

