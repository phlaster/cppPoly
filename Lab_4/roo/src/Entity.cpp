#include "headers/Entity.hpp"
#include <GL/freeglut.h>
#include <cmath>

v2 Entity:: windowSize;
int Entity::mainTime;
int Entity::radius;

void Entity::move() {
	pos.x += speed.x;
	pos.y += speed.y;
}
int Entity::create_random(int n) {
	return (rand() + time(NULL)) % n;
}
void Entity::setWindowSize(int W, int H) {
	windowSize.x = W;
	windowSize.y = H;
}
void Entity::drawPoly(int n) {
	double pi = 2 * acos(0.0);
	glBegin(GL_POLYGON); 
	for (int i = 0; i < n; ++i)
		glVertex2f(pos.x + radius * cos(2 * pi / n * i), pos.y + radius * sin(2 * pi / n * i));
	glEnd();
}
void Entity::setSpeed(v2 s) {
	speed = s;
}
void Entity::setRadius(int r) {
	radius = r;
}
v2 Entity::getPos() {
	return pos;
}
void Entity::globalClockReset() {
	mainTime = 0;
}
void Entity::globalClockTick() {
	mainTime++;
}