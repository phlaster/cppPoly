#ifndef INC_GAME_H
#define INC_GAME_H
#include "game_object.h"
#include "block.h"
#include "ball.h"
#include "bonus.h"
#include "paddle.h"


class game{
public:
	game() {
		block_size = { 50, 20 };
		game_object::setWindowSize(600, 600);
		game_object::globalClockReset();
		game_object::setRadius(10);
		block::setSize(block_size);
		ball::initBonuses();
		ball* p = new ball({ 0, 0 });
		ball::balls.insert(p);
		create_field();
	}

	void initGame(int argc, char** argv);
	void theLogic();
	static v2 touch(game_object* f, game_object* s);

private:
	void initGlutFunctions();
	void create_field();
	v2 block_size;
};

#endif
