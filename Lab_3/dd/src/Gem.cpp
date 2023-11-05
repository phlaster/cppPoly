#include "headers/Gem.hpp"

sf::Texture Gem::SPRITE;
float Gem::ONE_SPRITE_WIDTH;
size_t Gem::GEM_SIZE;

Gem::Gem(float x, float y, SpriteEnum sprite) : m_sprite(sprite) {
    sf::Vector2f size(Gem::ONE_SPRITE_WIDTH, Gem::ONE_SPRITE_WIDTH);

    this->m_gem.setSize(size);
    this->m_gem.setOrigin(size / 2.f);

    this->m_gem.setTexture(&Gem::SPRITE);
    this->m_gem.setTextureRect(
        sf::IntRect(
            static_cast<int>(Gem::ONE_SPRITE_WIDTH * static_cast<int>(sprite)), 0,
            static_cast<int>(Gem::ONE_SPRITE_WIDTH), static_cast<int>(Gem::ONE_SPRITE_WIDTH)
        )
    );

    this->m_gem.setPosition(x, y);
}

void Gem::setSprite(SpriteEnum sprite) {
    this->m_sprite = sprite;
    this->m_gem.setTextureRect(
        sf::IntRect(
            static_cast<int>(Gem::ONE_SPRITE_WIDTH * static_cast<int>(sprite)), 0,
            static_cast<int>(Gem::ONE_SPRITE_WIDTH), static_cast<int>(Gem::ONE_SPRITE_WIDTH)
        )
    );
}

int Gem::activate(GemTable& gems, size_t i, size_t j, size_t width, size_t height) {
    gems.at(i).at(j)->setSprite(SpriteEnum::SpriteEmpty);
    return static_cast<int>(ScoreEnum::RewardGem);
}

void Gem::hover(bool isHover) {
    if (isHover)
        this->m_gem.setScale(0.9f, 0.9f);
    else
        this->m_gem.setScale(1.f, 1.f);
}

sf::Vector2f Gem::getPosition() const {
    return this->m_gem.getPosition();
}

void Gem::setPosition(sf::Vector2f pos) {
    this->m_gem.setPosition(pos);
}

SpriteEnum Gem::getSprite() const {
    return m_sprite;
}

void Gem::draw(sf::RenderWindow* window) const {
    window->draw(this->m_gem);
}