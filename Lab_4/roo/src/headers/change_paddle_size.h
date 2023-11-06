#ifndef INC_CHANGE_PADDLE_SIZE
#define INC_CHANGE_PADDLE_SIZE
#include "bonus.h"
class change_paddle_size :
	public bonus
{
public:
	change_paddle_size(v2 p) :bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};

#endif