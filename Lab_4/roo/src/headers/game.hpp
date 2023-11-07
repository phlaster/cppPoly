#ifndef INC_GAME_H
#define INC_GAME_H
#include "game_object.hpp"
#include "block.hpp"
#include "Ball.hpp"
#include "bonus.hpp"
#include "paddle.hpp"


class game{
public:
	game();
	~game();
	void initGame(int argc, char** argv);
	void theLogic();
	static v2 touch(game_object* f, game_object* s);

private:
	void initGlutFunctions();
	void create_field();
	v2 block_size;
};

#endif
