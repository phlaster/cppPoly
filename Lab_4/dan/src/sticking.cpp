#include "headers/sticking.hpp"
#include "headers/slide.hpp"

void sticking::drawBonus() {
	drawNGon(8);
}
void sticking::activate() {
	slide::mainSlide->activateSticking();
}