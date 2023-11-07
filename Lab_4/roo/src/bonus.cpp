#include "headers/bonus.hpp"
#include "headers/Ball.hpp"
#include "headers/paddle.hpp"

std::set <bonus*> bonus::bonuses;

void bonus::drawAllBonuses() {
	glColor3f(1.0f, 0.5f, 0.31f);
	for (auto u : bonuses) {
		u->drawBonus();
	}
}

bool bonus::inGame() {
	if (pos.y > windowSize.y || pos.y < 0) return false;
	return true;
}

void add_ball::drawBonus() {
	drawPoly(20);
}
void add_ball::activate() {
	Ball* p = new Ball(pos);
}


void make_shield::activate() {
	Ball::makeShield();
}

void make_shield::drawBonus() {
	drawPoly(4);
}

void sticking::drawBonus() {
	drawPoly(3);
}
void sticking::activate() {
	paddle::mainPaddle->magnetize();
}