#ifndef INC_CHANGE_BALL_SPEED
#define INC_CHANGE_BALL_SPEED
#include "bonus.h"
class change_ball_speed :
	public bonus
{
public:
	change_ball_speed(v2 p) : bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};
#endif
