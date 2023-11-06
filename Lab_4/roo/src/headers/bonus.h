#ifndef INC_BONUS_H
#define INC_BONUS_H

#include "game_object.h"
#include <set>

class bonus : public game_object {
public:
    static std::set<bonus*> bonuses;

    bonus(v2 p) : game_object(p, { 0, -1.0 }) {
        bonuses.insert(this);
    }

    static void drawAllBonuses();
    virtual v2 getSize() override {
        return { radius * 2.0, radius * 2.0 };
    }

    virtual void activate() = 0;
    virtual bool isAlife() override;

    virtual ~bonus() {
        bonuses.erase(this);
    }

protected:
    virtual void drawBonus() = 0;
};

#endif