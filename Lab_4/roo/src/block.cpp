#include <GL/freeglut.h>

#include "headers/block.h"
#include "headers/bonus.h"

std::set <block*> block::blocks;
v2 block::size;

void block::setSize(v2 s) {
	size = s;
}

bool block::inGame() {
    return (hp > 0);
}

void block::drawBlock() {

	float greenComponent = 1.0 - hp / 3.0;
	float redComponent = hp / 3.0;
	float r,g,b;
	switch (hp){
		case 1:
			r=0.53; g=0.69; b=0.87;
			break;
		case 2:
			r=0.42; g=0.51; b=0.69;
			break;
		case 3:
			r=0.31; g=0.39; b=0.52;
			break;
		case 4:
			r=0.23; g=0.28; b=0.38;
			break;
		case 5:
			r=0.37; g=0.26; b=0.42;
			break;
	}
	glBegin(GL_QUADS);
	glColor3f(r, g, b); 
	glVertex2f(pos.x - size.x / 2, pos.y - size.y / 2);
	glVertex2f(pos.x - size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y + size.y / 2);
	glVertex2f(pos.x + size.x / 2, pos.y - size.y / 2);
	glEnd();
}

void block::drawAllBlocks() {
	for (auto u : blocks) {
		u->drawBlock();
	}
}

void block::touch() {
	if (hp != UNDEAD_THRESHOLD)
		hp--;
}

void block::create_bonus() {
	int var = create_random(3);
	bonus* p;
	switch (var) {
	case 0:
		p = new add_ball(pos);
		break;
	case 1:
		p = new make_shield(pos);
		break;
	case 2:
		p = new sticking(pos);
		break;
	}
}