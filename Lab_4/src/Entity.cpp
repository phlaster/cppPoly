#include "headers/Entity.hpp"
#include <GL/freeglut.h>
#include <cmath>

v2 Entity:: windowSize;
double Entity::radius;

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

bool Entity::touches(const Entity* other) const{
    double xOverlap = std::max(
        0.0,
        std::min(this->getPos().x + this->getSize().x / 2, other->getPos().x + other->getSize().x / 2) -
        std::max(this->getPos().x - this->getSize().x / 2, other->getPos().x - other->getSize().x / 2)
    );
    double yOverlap = std::max(
        0.0,
        std::min(this->getPos().y + this->getSize().y / 2, other->getPos().y + other->getSize().y / 2) -
        std::max(this->getPos().y - this->getSize().y / 2, other->getPos().y - other->getSize().y / 2)
    );

    return (xOverlap > 0 && yOverlap > 0);
}

void Entity::setSpeed(v2 s) {
	speed = s;
}

void Entity::setRadius(int r) {
	radius = r;
}

v2 Entity::getPos() const {
	return pos;
}
v2 Entity::getSize() const {
	return {radius, radius};
}