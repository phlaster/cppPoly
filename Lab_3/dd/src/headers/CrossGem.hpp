#ifndef CROSSGEM_HPP
#define CROSSGEM_HPP

#include "BonusGem.hpp"

class CrossGem : public BonusGem {
public:
    CrossGem(float x, float y, SpriteEnum sprite, SpriteEnum bonus);
    virtual int activate(GemTable& gems, size_t i, size_t j, size_t width, size_t height) override;
private:
    SpriteEnum bonusColor;
};

#endif