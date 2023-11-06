#include "headers/change_ball_speed.hpp"
#include "headers/ball.hpp"

void change_ball_speed::drawBonus() {
	drawNGon(4);
}
void change_ball_speed::activate() {
	ball::changeSpeed();
}