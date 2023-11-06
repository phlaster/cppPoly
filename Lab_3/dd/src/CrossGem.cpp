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
            int(Gem::ONE_SPRITE_WIDTH * int(bonus)),
            int(Gem::ONE_SPRITE_WIDTH),
            int(Gem::ONE_SPRITE_WIDTH), int(Gem::ONE_SPRITE_WIDTH)
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
    int dx[8] = { -1, 1, -1, 1, -2, 2, -2,  2};
    int dy[8] = { -1, -1, 1, 1, -2, 2,  2, -2};

    for (int k = 0; k < 8; k++) {
        int xi = i + dx[k];
        int xj = j + dy[k];

        if (
            xi >= 0 &&
            xi < height &&
            xj >= 0 &&
            xj < width &&
            gems.at(xi).at(xj)->getSprite() != SpriteEnum::SpriteEmpty) {
            gems.at(xi).at(xj)->setSprite(m_bonus);
        }
    }
    sf::Vector2f pos = this->getPosition();
    delete gems.at(i).at(j);
    gems.at(i).at(j) = new Gem(pos.x, pos.y, SpriteEnum::SpriteEmpty);

    return int(ScoreEnum::RewardX);
}
