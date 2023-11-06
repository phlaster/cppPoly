#include "headers/add_ball.h"
#include "headers/ball.h"
void add_ball::drawBonus() {
	drawNGon(3);
}
void add_ball::activate() {
	ball* p = new ball(pos);
}