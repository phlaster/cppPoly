#include "headers/slide.hpp"
#include <iostream>

slide* slide::mainSlide;
slide* sl = new slide;
void slide::changeSize() {
	change_size_time = mainTime;
}

void slide::drawSlide() {
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

void slide::moveLeft() {
	int sp = 50;
	if (mainTime - change_size_time <= delay && pos.x - size.x - sp < 0) {
		return;
	}
	if (mainTime - change_size_time > delay && pos.x - size.x / 2 - sp < 0) {
		return;
	}
	pos.x -= sp;
}

void slide::moveRight() {
	int sp = 50;
	
	if (mainTime - change_size_time <= delay && pos.x + size.x + sp > windowSize.x) {
		return;
	}
	if (mainTime - change_size_time > delay && pos.x + size.x / 2 + sp > windowSize.x) {
		return;
	}
	pos.x += sp;
}

void slide::activateSticking() {
	to_stick = true;
}

pair_t slide::getSize() {
	return size;
}