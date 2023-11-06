#ifndef INC_ADD_BALL_HPP
#define INC_ADD_BALL_HPP

#include "bonus.hpp"
class add_ball:
	public bonus
{
public:
	add_ball(pair_t p) :bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};

#endif
