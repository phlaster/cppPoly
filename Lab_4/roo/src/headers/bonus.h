#ifndef BONUSES_H
#define BONUSES_H

#include <GL/freeglut.h>
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
    virtual bool inGame() override;

    virtual ~bonus() {
        bonuses.erase(this);
    }

protected:
    virtual void drawBonus() = 0;
};



// class change_paddle_size : public bonus {
// public:
// 	change_paddle_size(v2 p) :bonus(p) {};
// 	virtual void drawBonus() override;
// 	virtual void activate() override;
// };



// class change_ball_speed : public bonus {
// public:
// 	change_ball_speed(v2 p) : bonus(p) {};
// 	virtual void drawBonus() override;
// 	virtual void activate() override;
// };


class add_ball : public bonus{
public:
	add_ball(v2 p) :bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};


class make_shield :	public bonus {
public:
	make_shield(v2 p) :bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};


class sticking : public bonus
{
public:
	sticking(v2 p) : bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};


#endif