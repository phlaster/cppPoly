#ifndef INC_CHANGE_BALL_SPEED_HPP
#define INC_CHANGE_BALL_SPEED_HPP

#include "bonus.hpp"
class change_ball_speed : public bonus
{
public:
	change_ball_speed(pair_t p) : bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};
#endif
