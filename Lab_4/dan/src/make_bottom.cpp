#include "headers/make_bottom.hpp"
#include "headers/ball.hpp"

void make_bottom::activate() {
	ball::makeBottom();
}

void make_bottom::drawBonus() {
	drawNGon(6);
}