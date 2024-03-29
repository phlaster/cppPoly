#ifndef BONUSES_H
#define BONUSES_H

#include <GL/freeglut.h>
#include "Entity.hpp"
#include <set>

class Bonus : public Entity {
public:
    static std::set<Bonus*> bonuses;

    Bonus(v2 p) : Entity(p, { 0, -1.0 }) {
        bonuses.insert(this);
    }
    virtual ~Bonus() {
        bonuses.erase(this);
    }

    static void drawAllBonuses();

    virtual void activate() = 0;
    virtual bool inGame() const override;


protected:
    virtual void drawBonus() = 0;
};


class add_ball : public Bonus{
public:
	add_ball(v2 p) :Bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};


class make_shield :	public Bonus {
public:
	make_shield(v2 p) :Bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};


class sticking : public Bonus{
public:
	sticking(v2 p) : Bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};


#endif