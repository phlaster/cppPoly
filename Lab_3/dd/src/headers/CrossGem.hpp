#ifndef CROSSGEM_HPP
#define CROSSGEM_HPP

#include "Gem.hpp"

class CrossGem : public Gem {
public:
    CrossGem(float x, float y, SpriteEnum sprite, SpriteEnum bonus);
    // virtual ~CrossGem() override;
    virtual void setPosition(sf::Vector2f pos) override;
    virtual void draw(sf::RenderWindow* window) const override;
    virtual int activate(GemTable& gems, size_t i, size_t j, size_t width, size_t height) override;
private:
    SpriteEnum m_bonus;
    sf::RectangleShape m_cross;
};

#endif