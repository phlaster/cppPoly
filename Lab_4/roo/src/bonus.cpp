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

void change_ball_speed::drawBonus() {
	drawPoly(4);
}
void change_ball_speed::activate() {
	ball::changeSpeed();
}



void change_paddle_size::drawBonus() {
	drawPoly(5);
}
void change_paddle_size::activate() {
	paddle::mainPaddle->changeSize();
}


void make_shield::activate() {
	ball::makeShield();
}

void make_shield::drawBonus() {
	drawPoly(6);
}

void sticking::drawBonus() {
	drawPoly(8);
}
void sticking::activate() {
	paddle::mainPaddle->activateSticking();
}