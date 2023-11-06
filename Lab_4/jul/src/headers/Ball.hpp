#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Paddle.hpp"


class Ball {
protected:
	float radius;
	float speedX, speedY;

	float x, y;

public:
	sf::Vector2f velocity;
	sf::CircleShape shape;
	bool isStart = false;
	Ball();
	~Ball() {};
	float getRadius();
	float getX();
	float getY();
	float getSpeedX();
	float getSpeedY();
	void setVelocity(sf::Vector2f velocity) {
		velocity = sf::Vector2f(velocity.x, velocity.y);
	}
	sf::Vector2f getVelocity() {
		return velocity;
	}
};