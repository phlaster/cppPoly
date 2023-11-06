#include "headers/game_object.hpp"
#include <cmath>

pair_t game_object:: windowSize;
int game_object::mainTime;
int game_object::delay; //the time of bonuses application
int game_object::radius; //for ball and bonus

void game_object::move() {
	pos.x += speed.x;
	pos.y += speed.y;
}

int game_object::create_random(int n) {
	return (rand() + time(NULL)) % n;
}

void game_object::drawNGon(int n) {
	double pi = 2 * std::acos(0.0);
	glBegin(GL_POLYGON);
	//glColor3f(0.9f, 0.9f, 0.9f);
	for (int i = 0; i < n; ++i)
		glVertex2f(pos.x + radius * std::cos(2 * pi / n * i), pos.y + radius * std::sin(2 * pi / n * i));
	glEnd();
}