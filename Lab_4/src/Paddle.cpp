#include "headers/Paddle.hpp"
#include <GL/freeglut.h>
#include <cmath>


Paddle* Paddle::mainPaddle;
Paddle* sl = new Paddle;

void Paddle::drawPaddle() {
	glBegin(GL_QUADS);

	if (!isMagnetic)
	 	glColor3f(0.58f, 0.52f, 0.97f);
	else
		glColor3f(0.29f, 0.18f, 0.96f);

	pos.x += speed.x;

	glVertex2f(pos.x - size.x / 2, pos.y - size.y / 2);
	glVertex2f(pos.x - size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y - size.y / 2);
	stop();
	glEnd();
}

void Paddle::moveLeft() {
	if (pos.x - size.x/1.5 > 0){
		if (std::fabs(speed.x == 0)){
			speed.x = -25;
		}
		speed.x = -12;
	}

}
void Paddle::moveRight() {
	if (pos.x + size.x/1.5 < windowSize.x){
		if (std::fabs(speed.x == 0)){
			speed.x = 25;
		}
		speed.x = 12;
	}
}

void Paddle::stop(){
	speed.x /= 1.4;
}

void Paddle::magnetize() {
	isMagnetic = true;
}

v2 Paddle::getSize() {
	return size;
}

bool Paddle::isReadyToStick() {
	return isMagnetic;
}
void Paddle::unMagnit() {
	isMagnetic = false;
}
bool Paddle::inGame() {
	return true;
}