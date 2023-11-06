#ifndef INC_BONUS_HPP
#define INC_BONUS_HPP

#include "game_object.hpp"
#include <set>
class bonus :
    public game_object
{
public:
    static std::set<bonus*> bonuses;
    bonus(pair_t p) : game_object(p, { 0, -1 }){
        bonuses.insert(this);
    }
    static void drawAllBonuses();
    virtual  pair_t getSize() override{
        return { radius * 2, radius * 2};
    }
    virtual void activate() = 0;
    virtual bool isAlife() override;
    ~bonus() {
        bonuses.erase(this);
    }

protected:
    virtual void drawBonus() = 0;
};
#endif
