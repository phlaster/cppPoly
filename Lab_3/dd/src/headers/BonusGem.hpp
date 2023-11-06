#ifndef BONUSGEM_HPP
#define BONUSGEM_HPP

#include "Gem.hpp"

class BonusGem : public Gem {
public:
    sf::RectangleShape BonusFrame;
    
    BonusGem(float x, float y, SpriteEnum sprite) : Gem(x,y,sprite){};

    virtual void setPosition(sf::Vector2f pos) override{
        Gem::setPosition(pos);
        this->BonusFrame.setPosition(pos);
    };
    virtual void draw(sf::RenderWindow* window) const override{
        Gem::draw(window);
        window->draw(this->BonusFrame);
    };
    virtual int activate(GemTable& gems, size_t i, size_t j, size_t width, size_t height) override = 0;
protected:
};

#endif