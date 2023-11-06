#include "headers/Paddle.hpp"
#include "headers/Source.hpp"

Paddle::Paddle() 
{
	width = PADDLE_WIDTH;
	height = PADDLE_HEIGHT;
	shape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
	x = PADDLE_POS_X;
	y = PADDLE_POS_Y;
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(x, y);

}



float Paddle::GetPosX(void)
{
	return x;
}

float Paddle::GetPosY(void)
{
	return y;
}

