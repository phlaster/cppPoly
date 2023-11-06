#ifndef INC_GAME_HPP
#define INC_GAME_HPP



#include "game_object.hpp"
#include "block.hpp"
#include "ball.hpp"
#include "bonus.hpp"
#include "slide.hpp"


class game {
public:
	game() {
		block_size = { 50, 20 };
		game_object::setWindowSize(600, 600);
		game_object::setDealay(50000);
		game_object::setMainTime();
		game_object::setRadius(10);
		block::setSize(block_size);
		ball::initBonuses();
		ball* p = new ball({ 0, 0 });
		create_field();
		
	}

	void initGame(int argc, char** argv);
	void mechanic();
	static pair_t touch(game_object* f, game_object* s);

private:
	void initGlutFunctions();
	void create_field();
	pair_t block_size;
};

#endif
