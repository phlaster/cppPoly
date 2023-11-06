#include "headers/Gem.hpp"

sf::Texture Gem::SPRITE;
float Gem::ONE_SPRITE_WIDTH;
size_t Gem::GEM_SIZE;

Gem::Gem(float x, float y, SpriteEnum sprite) : m_sprite(sprite) {
    sf::Vector2f size(Gem::ONE_SPRITE_WIDTH, Gem::ONE_SPRITE_WIDTH);

    this->gemBody.setSize(size);
    this->gemBody.setOrigin(size / 2.f);

    this->gemBody.setTexture(&Gem::SPRITE);
    this->gemBody.setTextureRect(
        sf::IntRect(
            int(Gem::ONE_SPRITE_WIDTH * int(sprite)), 0,
            int(Gem::ONE_SPRITE_WIDTH), int(Gem::ONE_SPRITE_WIDTH)
        )
    );

    this->gemBody.setPosition(x, y);
}

void Gem::setSprite(SpriteEnum sprite) {
    this->m_sprite = sprite;
    this->gemBody.setTextureRect(
        sf::IntRect(
            int(Gem::ONE_SPRITE_WIDTH * int(sprite)), 0,
            int(Gem::ONE_SPRITE_WIDTH), int(Gem::ONE_SPRITE_WIDTH)
        )
    );
}

int Gem::activate(GemTable& gems, size_t i, size_t j, size_t width, size_t height) {
    if (i<height && j<width){
        gems.at(i).at(j)->setSprite(SpriteEnum::SpriteEmpty);
        return int(ScoreEnum::RewardGem);
    } else {
        return 0;
    }
}

void Gem::hover(bool isHover) {
    if (isHover)
        this->gemBody.setScale(1.2, 1.2);
    else
        this->gemBody.setScale(1.0, 1.0);
}

sf::Vector2f Gem::getPosition() const {
    return this->gemBody.getPosition();
}

void Gem::setPosition(sf::Vector2f pos) {
    this->gemBody.setPosition(pos);
}

SpriteEnum Gem::getSprite() const {
    return m_sprite;
}

void Gem::draw(sf::RenderWindow* window) const {
    window->draw(this->gemBody);
}