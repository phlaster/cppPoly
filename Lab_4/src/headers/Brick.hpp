#ifndef INC_BLOCK_H
#define INC_BLOCK_H
#include <ctime>
#include <set>
#include "Bonus.hpp"
#define UNDEAD_THRESHOLD 5

class Brick : public Entity {
public:
    static std::set<Brick*> blocks;
    Brick(v2 p);
    Brick(v2 p, int hp);
    void touch();
    int getHP();
    virtual bool inGame() override;
    static void setSize(v2 s);
    static void drawAllBlocks();

    virtual v2 getSize() override;
    virtual ~Brick();

private:
    int hp;
    static v2 size;
    void drawBlock();
    void create_bonus();
};
#endif

