#include "headers/bonus.h"
#include <GL/freeglut.h>

std::set <bonus*> bonus::bonuses;

void bonus::drawAllBonuses() {
	glColor3f(1.0f, 0.5f, 0.31f);
	for (auto u : bonuses) {
		u->drawBonus();
	}
}

bool bonus::isAlife() {
	if (pos.y > windowSize.y || pos.y < 0) return false;
	return true;
}
