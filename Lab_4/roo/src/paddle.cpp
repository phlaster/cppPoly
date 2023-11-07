#include "headers/paddle.h"
#include <GL/freeglut.h>
#include <cmath>


paddle* paddle::mainPaddle;
paddle* sl = new paddle;

void paddle::drawPaddle() {
	glBegin(GL_QUADS);

	if (!isMagnetic)
	 	glColor3f(0.58f, 0.52f, 0.97f);
	else
		glColor3f(0.29f, 0.18f, 0.96f);

	pos.x += speed.x;

	glVertex2f(pos.x - size.x / 2, pos.y - size.y / 2);
	glVertex2f(pos.x - size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y - size.y / 2);
	stop();
	glEnd();
}

void paddle::moveLeft() {
	if (pos.x - size.x/1.5 > 0){
		if (std::fabs(speed.x == 0)){
			speed.x = -25;
		}
		speed.x = -12;
	}

}
void paddle::moveRight() {
	if (pos.x + size.x/1.5 < windowSize.x){
		if (std::fabs(speed.x == 0)){
			speed.x = 25;
		}
		speed.x = 12;
	}
}

void paddle::stop(){
	speed.x /= 1.4;
}

void paddle::magnetize() {
	isMagnetic = true;
}

v2 paddle::getSize() {
	return size;
}