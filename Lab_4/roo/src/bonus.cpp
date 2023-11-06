#include "headers/bonus.h"
#include "headers/ball.h"
#include "headers/paddle.h"

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
	ball* p = new ball(pos);
}


void make_shield::activate() {
	ball::makeShield();
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