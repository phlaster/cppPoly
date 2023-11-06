#include "headers/change_slide_size.hpp"
#include "headers/slide.hpp"
void change_slide_size::drawBonus() {
	drawNGon(5);
}
void change_slide_size::activate() {
	slide::mainSlide->changeSize();
}