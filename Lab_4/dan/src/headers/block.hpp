#ifndef INC_BLOCK_HPP
#define INC_BLOCK_HPP

#include <ctime>
#include <set>
#include "bonus.hpp"
#define absolut 5

class block :
    public game_object
{
public:
    static std::set<block*> blocks;
    block(pair_t p) : game_object(p), hp(create_random(5) + 1) {
        blocks.insert(this);
    };

    void touch();
    int getHP() {
        return hp;
    }
    virtual bool isAlife() override;
    static void setSize(pair_t s);
    static void drawAllBlocks();

    virtual pair_t getSize() override{
        return size;
    }

    ~block() {
        blocks.erase(this);
        int chance = create_random(2);
        if (chance == 0) create_bonus();
    }

private:
    int hp;
    static pair_t size;
    void drawBlock();
    void create_bonus();
};
#endif

