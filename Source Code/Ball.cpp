#include "Ball.h"
#include <cmath>

Ball::Ball(float ballRadius, float velocity)
	:ballVelocity(velocity)
{
	body.setRadius(ballRadius);
	body.setOrigin(ballRadius / 2, ballRadius / 2);
	body.setFillColor(sf::Color::White);

	SetStartPosition();
}

void Ball::CheckCollision(Rocket& player1, Rocket& player2, bool& pause)
{
	// k = [0.95, 1.05]
	float k = (rand() % 101 + 950.0f) / 1000.0f;

	sf::Vector2f ball = body.getPosition();
	float ball_radius = body.getRadius();

	sf::Vector2f p1 = player1.body.getPosition();
	sf::Vector2f p1_size = player1.body.getSize();

	sf::Vector2f p2 = player2.body.getPosition();
	sf::Vector2f p2_size = player2.body.getSize();

	// Up and Down Walls Collisions
	if (ball.y - ball_radius < 0)
		if (velocity.y < 0)
			velocity.y = -velocity.y * k;

	if (body.getPosition().y + ball_radius > screenY)
		if (velocity.y > 0)
			velocity.y = -velocity.y * k;

	// Collision with players
	if (abs(p1.x - ball.x) < ball_radius + p1_size.x / 2 &&
		abs(p1.y - ball.y) < ball_radius + p1_size.y / 2)
		if (velocity.x < 0)
			velocity.x = -velocity.x * k;
	if (abs(p2.x - ball.x) < ball_radius + p2_size.x / 2 &&
		abs(p2.y - ball.y) < ball_radius + p2_size.y / 2)
		if (velocity.x > 0)
			velocity.x = -velocity.x * k;

	// Winning cases
	if (ball.x < 0 || ball.x > screenX)
	{
		if (ball.x < 0)
			player2.score++;
		else
			player1.score++;

		player1.SetStartPosition();
		player2.SetStartPosition();
		SetStartPosition();
		pause = true;
	}
	while (velocity.x * velocity.x + velocity.y * velocity.y > 1.2 * 1.2 * ballVelocity * ballVelocity)
	{
		if (abs(velocity.x) > abs(velocity.y) * 0.9 / sqrt(1 - 0.9 * 0.9))
			velocity.x *= 0.999;
		else if (abs(velocity.x) < abs(velocity.y) * 0.5 / sqrt(1 - 0.5 * 0.5))
			velocity.y *= 0.999;
		else
		{
			if (rand() % 2 == 0)
				velocity.y *= 0.999;
			else
				velocity.x *= 0.999;
		}
	}
	while (velocity.x * velocity.x + velocity.y * velocity.y < 0.8 * 0.8 * ballVelocity * ballVelocity)
	{
		if (abs(velocity.x) > 0.9 / sqrt(1 - 0.9 * 0.9) * abs(velocity.y))
			velocity.y = velocity.y * 1.001;
		else if (abs(velocity.x) < 0.5 / sqrt(1 - 0.5 * 0.5) * abs(velocity.y))
			velocity.x = velocity.x * 1.001;
		else
		{
			if (rand() % 2 == 0)
				velocity.y  *= 1.001;
			else
				velocity.x *= 1.001;
		}
	}
}

void Ball::Update(Rocket& player1, Rocket& player2, float deltaTime, bool& pause)
{
	CheckCollision(player1, player2, pause);
	if (!pause)
		body.move(velocity * deltaTime);
}


void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Ball::SetStartPosition()
{
	body.setPosition(screenX / 2, screenY / 2);
	// k = [0.5, 0.9]
	float k = (rand() % 401 + 500.0f) / 1000.0f;
	int s1 = 2 * (rand() % 2) - 1;
	int s2 = 2 * (rand() % 2) - 1;
	velocity.x = ballVelocity * s1 * k;
	velocity.y = ballVelocity * s2 * sqrt(1.0f - k * k);
}
