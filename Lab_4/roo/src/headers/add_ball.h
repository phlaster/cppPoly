#ifndef INC_ADD_BALL_H
#define INC_ADD_BALL_H
#include "bonus.h"
class add_ball:
	public bonus
{
public:
	add_ball(v2 p) :bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};
#endif
