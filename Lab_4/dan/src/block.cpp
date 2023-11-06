#include "headers/block.hpp"
#include "headers/add_ball.hpp"
#include "headers/change_ball_speed.hpp"
#include "headers/change_slide_size.hpp"
#include "headers/sticking.hpp"
#include "headers/make_bottom.hpp"

std::set <block*> block::blocks;
pair_t block::size;

void block::setSize(pair_t s) {
	size = s;
}

bool block::isAlife() {
    return (hp > 0);
}

void block::drawBlock() {
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1 - double(hp)/10.0, double(hp) / 5.0);
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
	if (hp != absolut)
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
		p = new change_slide_size(pos);
		break;
	case 3:
		p = new make_bottom(pos);
		break;
	case 4:
		p = new sticking(pos);
		break;
	}
}