#ifndef INC_BLOCK_H
#define INC_BLOCK_H
#include <ctime>
#include <set>
#include "bonus.h"
#define UNDEAD_THRESHOLD 5

class block : public game_object
{
public:
    static std::set<block*> blocks;
    block(v2 p) : game_object(p), hp(create_random(UNDEAD_THRESHOLD) + 1) {
        blocks.insert(this);
    };

    void touch();
    int getHP() {
        return hp;
    }
    virtual bool isAlife() override;
    static void setSize(v2 s);
    static void drawAllBlocks();

    virtual v2 getSize() override{
        return size;
    }

    virtual ~block() {
        blocks.erase(this);
        int chance = create_random(2);
        if (chance == 0) create_bonus();
    }

private:
    int hp;
    static v2 size;
    void drawBlock();
    void create_bonus();

};
#endif

