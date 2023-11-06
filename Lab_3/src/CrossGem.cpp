#include "headers/CrossGem.hpp"
#include <cstdlib>

CrossGem::CrossGem(float x, float y, SpriteEnum sprite, SpriteEnum bonus)
    : BonusGem(x, y, sprite), bonusColor(bonus)
{
    sf::Vector2f size(Gem::ONE_SPRITE_WIDTH, Gem::ONE_SPRITE_WIDTH);
    this->BonusFrame.setSize(size);
    this->BonusFrame.setOrigin(size / 2.f);

    this->BonusFrame.setTexture(&Gem::SPRITE);
    this->BonusFrame.setTextureRect(
        sf::IntRect(
            int(Gem::ONE_SPRITE_WIDTH * int(bonus)),
            int(Gem::ONE_SPRITE_WIDTH),
            int(Gem::ONE_SPRITE_WIDTH), int(Gem::ONE_SPRITE_WIDTH)
        )
    );

    this->BonusFrame.setPosition(x, y);
}

int CrossGem::activate(GemTable& gems, size_t i, size_t j, size_t width, size_t height) {
    int dx[8] = { -1, 1, -1, 1, -2, 2, -2,  2};
    int dy[8] = { -1, -1, 1, 1, -2, 2,  2, -2};

    for (int k = 0; k < 8; k++) {
        int xi = i + dx[k];
        int xj = j + dy[k];

        if (
            xi >= 0 &&
            xi < int(height) &&
            xj >= 0 &&
            xj < int(width) &&
            gems.at(xi).at(xj)->getSprite() != SpriteEnum::SpriteEmpty) {
            gems.at(xi).at(xj)->setSprite(bonusColor);
        }
    }
    sf::Vector2f pos = this->getPosition();
    delete gems.at(i).at(j);
    gems.at(i).at(j) = new Gem(pos.x, pos.y, SpriteEnum::SpriteEmpty);

    return int(ScoreEnum::RewardX);
}
