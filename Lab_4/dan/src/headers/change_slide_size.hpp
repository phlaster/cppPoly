#ifndef INC_CHANGE_SLIDE_SIZE_HPP
#define INC_CHANGE_SLIDE_SIZE_HPP

#include "bonus.hpp"
class change_slide_size : public bonus
{
public:
	change_slide_size(pair_t p) :bonus(p) {};
	virtual void drawBonus() override;
	virtual void activate() override;
};

#endif