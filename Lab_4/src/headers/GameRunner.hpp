#ifndef INC_GAME_H
#define INC_GAME_H
#include "Entity.hpp"
#include "Brick.hpp"
#include "Ball.hpp"
#include "Bonus.hpp"
#include "Paddle.hpp"


class GameRunner{
public:
	GameRunner();
	~GameRunner();
	void initGame(int argc, char** argv);
	void theLogic();
	static v2 touch(Entity* f, Entity* s);

private:
	void initGlutFunctions();
	void create_field();
	v2 block_size;
};

#endif
