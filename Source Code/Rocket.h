#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

extern float screenY;
extern float screenX;

class Rocket
{
public:
	Rocket(bool positionLeft, float speed);
	void Update(int direction, float deltaTime);
	void Draw(sf::RenderWindow& window);
	void SetStartPosition();
	void DrawScore(sf::RenderWindow& window, sf::Text text);


public:
	sf::RectangleShape body;
	int score;

private:
	bool positionLeft;
	float speed;
};

