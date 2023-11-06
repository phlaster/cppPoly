#include "headers/change_paddle_size.h"
#include "headers/paddle.h"
void change_paddle_size::drawBonus() {
	drawNGon(5);
}
void change_paddle_size::activate() {
	paddle::mainPaddle->changeSize();
}