#include "headers/paddle.h"
#include <GL/freeglut.h>
#include <iostream>

paddle* paddle::mainPaddle;
paddle* sl = new paddle;
void paddle::changeSize() {
	change_size_time = mainTime;
}

void paddle::drawPaddle() {
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.0f, 0.3f);
	glVertex2f(pos.x - size.x / 2, pos.y - size.y / 2);
	glVertex2f(pos.x - size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y - size.y / 2);
	glEnd();
}

void paddle::moveLeft() {
	if (pos.x - size.x > 0){
		pos.x -= 10 * 5;
	}

}

void paddle::moveRight() {
	if (pos.x + size.x < windowSize.x){
		pos.x += 10 * 5;
	}
}

void paddle::activateSticking() {
	to_stick = true;
}

v2 paddle::getSize() {
	return size;
}