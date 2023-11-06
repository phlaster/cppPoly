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

	float greenComponent = 1.0f - static_cast<float>(hp) / 3.0f;
	float redComponent = static_cast<float>(hp) / 3.0f;

	if (greenComponent < 0.0f) greenComponent = 0.0f;
	if (redComponent > 1.0f) redComponent = 1.0f;

	glBegin(GL_QUADS);
	glColor3f(redComponent, greenComponent, 0.0f); 
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
	int var = create_random(5);
	bonus* p;
	switch (var) {
	case 0:
		p = new add_ball(pos);
		break;
	case 1:
		p = new change_ball_speed(pos);
		break;
	case 2:
		p = new change_paddle_size(pos);
		break;
	case 3:
		p = new make_shield(pos);
		break;
	case 4:
		p = new sticking(pos);
		break;
	}
}