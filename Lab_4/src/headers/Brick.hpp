#ifndef INC_BLOCK_H
#define INC_BLOCK_H
#include <ctime>
#include <set>
#include "Entity.hpp"

const int UNDEAD_THRESHOLD = 5;

class Brick : public Entity {
public:
    static std::set<Brick*> blocks;
    Brick(v2 p);
    Brick(v2 p, int hp);
    virtual ~Brick();
    void loose_hp();
    int getHP();
    
    virtual bool inGame() const override;
    virtual v2 getSize() const override;

    static void setSize(v2 s);
    static void drawAllBlocks();
private:
    int hp;
    static v2 size;
    void drawBlock();
    void create_bonus();
};
#endif

