#include "headers/Ball.hpp"
#include "headers/Source.hpp"
#include <algorithm>
#include <iostream>



Ball::Ball()
{
	shape.setRadius(BALL_RADIUS);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(BALL_POS_X, BALL_POS_Y);
	speedX =0;
	velocity = sf::Vector2f(-SPEED, -SPEED);
}
float Ball::getRadius()
{
	return radius;
}

float Ball::getX()
{
	return x;
}

float Ball::getY()
{
	return y;
}

float Ball::getSpeedX()
{
	return speedX;
}

float Ball::getSpeedY()
{
	return speedY;
}
