#ifndef INC_GAME_H
#define INC_GAME_H
#include "Entity.hpp"
#include <vector>

using Field = std::vector<std::vector<int>>;

class GameRunner{
public:
	GameRunner();
	~GameRunner();
	void initGame(int argc, char** argv);
	void theLogic();
	// static const bool are_touching(Entity* a, Entity* b);

private:
	void initGlutFunctions();
	void create_field(const Field& field);
	v2 block_size;
};

#endif
