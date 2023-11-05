#include "headers/CrossGem.hpp"
#include <cstdlib>

CrossGem::CrossGem(float x, float y, SpriteEnum sprite, SpriteEnum bonus)
    : Gem(x, y, sprite), m_bonus(bonus)
{
    sf::Vector2f size(Gem::ONE_SPRITE_WIDTH, Gem::ONE_SPRITE_WIDTH);
    this->m_cross.setSize(size);
    this->m_cross.setOrigin(size / 2.f);

    this->m_cross.setTexture(&Gem::SPRITE);
    this->m_cross.setTextureRect(
        sf::IntRect(
            static_cast<int>(Gem::ONE_SPRITE_WIDTH * static_cast<int>(bonus)),
            static_cast<int>(Gem::ONE_SPRITE_WIDTH),
            static_cast<int>(Gem::ONE_SPRITE_WIDTH), static_cast<int>(Gem::ONE_SPRITE_WIDTH)
        )
    );

    this->m_cross.setPosition(x, y);
}

void CrossGem::setPosition(sf::Vector2f pos) {
    Gem::setPosition(pos);
    this->m_cross.setPosition(pos);
}

void CrossGem::draw(sf::RenderWindow* window) const {
    Gem::draw(window);
    window->draw(this->m_cross);
}

int CrossGem::activate(GemTable& gems, size_t i, size_t j, size_t width, size_t height) {
    int xi = static_cast<int>(i) + ((rand() % 2) ? -1 : 1);
    int xj = static_cast<int>(j) + ((rand() % 2) ? -1 : 1);
    int xi1 = static_cast<int>(i) + ((rand() % 2) ? -1 : 1);
    int xj1 = static_cast<int>(j) + ((rand() % 2) ? -1 : 1);

    while (xi == xi1) xi1 = static_cast<int>(i) + ((rand() % 2) ? -1 : 1);
    while(xj == xj1) xj1 = static_cast<int>(j) + ((rand() % 2) ? -1 : 1);

    if (xi >= 0 && xj >= 0 && xi < height && xj < width && gems.at(xi).at(xj)->getSprite() != SpriteEnum::SpriteEmpty)
        gems.at(xi).at(xj)->setSprite(m_bonus);

    if (xi1 >= 0 && xj1 >= 0 && xi1 < height && xj1 < width && gems.at(xi1).at(xj1)->getSprite() != SpriteEnum::SpriteEmpty)
        gems.at(xi1).at(xj1)->setSprite(m_bonus);

    sf::Vector2f pos = this->getPosition();
    delete gems.at(i).at(j);
    gems.at(i).at(j) = new Gem(pos.x, pos.y, SpriteEnum::SpriteEmpty);

    return static_cast<int>(ScoreEnum::RewardX);
}