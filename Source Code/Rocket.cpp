#include "Rocket.h"
#include <string>

Rocket::Rocket(bool positionLeft, float speed)
	:speed(speed), positionLeft(positionLeft), score(0)
{
	body.setFillColor(sf::Color::White);
	SetStartPosition();
}

void Rocket::Update(int direction, float deltaTime)
{
	float change = direction * speed * deltaTime;
	float currentPosition = body.getPosition().y;
	if (currentPosition + change < body.getSize().y / 2)
		change = body.getSize().y / 2 - currentPosition;
	else if (currentPosition + change > screenY - body.getSize().y / 2)
		change = screenY - body.getSize().y / 2 - currentPosition;
	body.move(0, change);
}

void Rocket::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Rocket::SetStartPosition()
{
	sf::Vector2f size = sf::Vector2f(15, screenY / 4);
	body.setSize(size);
	if (positionLeft)
	{
		body.setOrigin(size.x / 2, size.y / 2);
		body.setPosition(size.x / 2, screenY / 2);
	}
	else
	{
		body.setOrigin(size.x / 2, size.y / 2);
		body.setPosition(screenX - size.x / 2, screenY / 2);
	}
}

void Rocket::DrawScore(sf::RenderWindow& window, sf::Text text)
{
	text.setString(std::to_string(score));
	if (positionLeft)
		text.setPosition(screenX / 3, 0);
	else
		text.setPosition(2 * screenX / 3, 0);
	window.draw(text);
}
