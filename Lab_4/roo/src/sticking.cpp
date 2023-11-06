#include "headers/sticking.h"
#include "headers/paddle.h"

void sticking::drawBonus() {
	drawNGon(8);
}
void sticking::activate() {
	paddle::mainPaddle->activateSticking();
}