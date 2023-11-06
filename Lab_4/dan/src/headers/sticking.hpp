#ifndef INC_STICKING_HPP
#define INC_STICKING_HPP
#include "bonus.hpp"
class sticking :
    public bonus
{
public:
	sticking(pair_t p) : bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};
#endif
