#pragma once
#include <SFML/Graphics.hpp>
#define BAR_SPEED 34

class Paddle {
protected:
	float height, width;
	float x, y;

public:

	Paddle();
	sf::RectangleShape shape;
	~Paddle(void) {};

	float GetHeight(void);
	float GetWidth(void);
	float GetPosX(void);
	float GetPosY(void);
	float getX() { return x; }
	float getY() { return y; }
};