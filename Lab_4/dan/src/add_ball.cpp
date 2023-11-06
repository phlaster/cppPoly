#include "headers/add_ball.hpp"
#include "headers/ball.hpp"
void add_ball::drawBonus() {
	drawNGon(3);
}
void add_ball::activate() {
	ball* p = new ball(pos);
}