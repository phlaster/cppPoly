#include "headers/make_bottom.h"
#include "headers/ball.h"

void make_bottom::activate() {
	ball::makeBottom();
}

void make_bottom::drawBonus() {
	drawNGon(6);
}