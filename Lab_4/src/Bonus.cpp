#include "headers/Bonus.hpp"
#include "headers/Ball.hpp"
#include "headers/Paddle.hpp"

std::set <Bonus*> Bonus::bonuses;

void Bonus::drawAllBonuses() {
	glColor3f(1.0f, 0.5f, 0.31f);
	for (auto u : bonuses) {
		u->drawBonus();
	}
}

bool Bonus::inGame() const {
	return (pos.y < windowSize.y && pos.y > 0);
}

void add_ball::drawBonus() {
	drawPoly(20);
}
void add_ball::activate() {
	new Ball(pos);
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
	Paddle::mainPaddle->magnetize();
}