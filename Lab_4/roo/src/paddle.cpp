#include "headers/paddle.h"
#include <GL/freeglut.h>
#include <iostream>

paddle* paddle::mainPaddle;
paddle* sl = new paddle;
void paddle::changeSize() {
	change_size_time = mainTime;
}

void paddle::drawPaddle() {
	if (mainTime - change_size_time < delay) {
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(pos.x - size.x, pos.y - size.y / 2);
		glVertex2f(pos.x - size.x, pos.y + size.y / 2);
		glVertex2f(pos.x + size.x, pos.y + size.y / 2);
		glVertex2f(pos.x + size.x, pos.y - size.y / 2);
		glEnd();
	}
	else {
		glBegin(GL_QUADS);
		glColor3f(0.5f, 0.0f, 0.3f);
		glVertex2f(pos.x - size.x / 2, pos.y - size.y / 2);
		glVertex2f(pos.x - size.x / 2, pos.y + size.y / 2);
		glVertex2f(pos.x + size.x / 2, pos.y + size.y / 2);
		glVertex2f(pos.x + size.x / 2, pos.y - size.y / 2);
		glEnd();
	}
}

void paddle::moveLeft() {
	int sp = 5;
	if (mainTime - change_size_time <= delay && pos.x - size.x - sp < 0) {
		return;
	}
	if (mainTime - change_size_time > delay && pos.x - size.x / 2 - sp < 0) {
		return;
	}
	pos.x -= 10 * sp;
}

void paddle::moveRight() {
	int sp = 5;
	if (mainTime - change_size_time <= delay && pos.x + size.x + sp > windowSize.x) {
		return;
	}
	if (mainTime - change_size_time > delay && pos.x + size.x / 2 + sp > windowSize.x) {
		return;
	}
	pos.x += 10 * sp;
}

void paddle::activateSticking() {
	to_stick = true;
}

v2 paddle::getSize() {
	return size;
}