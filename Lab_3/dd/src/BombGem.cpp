#include "headers/BombGem.hpp"
#include <cstddef>
#include <cstdlib>

BombGem::BombGem(float x, float y, SpriteEnum sprite)
    : BonusGem(x, y, sprite)
{
    sf::Vector2f size(Gem::ONE_SPRITE_WIDTH, Gem::ONE_SPRITE_WIDTH);
    this->BonusFrame.setSize(size);
    this->BonusFrame.setOrigin(size / 2.f);

    this->BonusFrame.setTexture(&Gem::SPRITE);
    this->BonusFrame.setTextureRect(
        sf::IntRect(
            int(Gem::ONE_SPRITE_WIDTH * int(BonusEnum::BonusBomb)), 
            int(Gem::ONE_SPRITE_WIDTH),
            int(Gem::ONE_SPRITE_WIDTH), int(Gem::ONE_SPRITE_WIDTH)
        )
    );

    this->BonusFrame.setPosition(x, y);
}

int BombGem::activate(GemTable& gems, size_t i, size_t j, size_t width, size_t height) {
    Gem* tmp = gems.at(i).at(j);
    size_t score = 0;
    sf::Vector2f pos = this->getPosition();
    gems.at(i).at(j) = new Gem(pos.x, pos.y, SpriteEnum::SpriteEmpty);

    size_t ni = rand() % height;
    size_t nj = rand() % width;

    score += gems.at(ni).at(nj)->activate(gems, ni, nj, width, height);

    if (ni + 1 < height)
        score += gems.at(ni).at(nj)->activate(gems, ni + 1, nj, width, height);

    if (nj + 1 < width)
        score += gems.at(ni).at(nj)->activate(gems, ni, nj + 1, width, height);

    if (ni - 1 >= 0)
        score += gems.at(ni).at(nj)->activate(gems, ni - 1, nj, width, height);

    if (nj - 1 >= 0)
        score += gems.at(ni).at(nj)->activate(gems, ni, nj - 1, width, height);

    delete tmp;
    return int(ScoreEnum::RewardBomb) + score;
}