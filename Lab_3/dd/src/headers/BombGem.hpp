#ifndef BOMBGEM_HPP
#define BOMBGEM_HPP

#include "BonusGem.hpp"


class BombGem : public BonusGem {
public:
    BombGem(float x, float y, SpriteEnum sprite);
    virtual int activate(GemTable& gems, size_t i, size_t j, size_t width, size_t height) override;
};

#endif