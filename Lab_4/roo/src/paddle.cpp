#include "headers/paddle.h"
#include <GL/freeglut.h>
#include <iostream>

paddle* paddle::mainPaddle;
paddle* sl = new paddle;

void paddle::drawPaddle() {
	glBegin(GL_QUADS);

	if (!isMagnetic)
		glColor3f(0.5f, 0.5f, 0.6f);
	else
	 	glColor3f(0.7f, 0.4f, 0.7f);

	pos.x += speed.x;

	glVertex2f(pos.x - size.x / 2, pos.y - size.y / 2);
	glVertex2f(pos.x - size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y - size.y / 2);
	stop();
	glEnd();
}

void paddle::moveLeft() {
	if (pos.x - size.x > 0){
		speed.x = -12;
	}

}
void paddle::moveRight() {
	if (pos.x + size.x < windowSize.x){
		speed.x = 12;
	}
}

void paddle::stop(){
	speed.x = 0;
}

void paddle::magnetize() {
	isMagnetic = true;
}

v2 paddle::getSize() {
	return size;
}