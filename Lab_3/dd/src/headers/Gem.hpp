#ifndef GEM_HPP
#define GEM_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class Gem;

using GemTable = std::vector<std::vector<Gem*>>;

enum class ScoreEnum {
    RewardGem = 1,
    RewardX = 2,
    RewardBomb = 7
};

enum class SpriteEnum {
    SpriteRed = 0,
    SpriteEmerald,
    SpriteBlue,
    SpriteOrange,
    SpriteEmpty
};

enum class BonusEnum {
    BonusRedX = 0,
    BonusEmeraldX,
    BonusBlueX,
    BonusOrangeX,
    BonusBomb
};


class Gem{
private:
    SpriteEnum m_sprite;
    sf::RectangleShape gemBody;

public:
    static sf::Texture SPRITE;
    static float ONE_SPRITE_WIDTH;
    static size_t GEM_SIZE;

    Gem(float x, float y, SpriteEnum sprite);
    virtual ~Gem() {}
    SpriteEnum getSprite() const;
    sf::Vector2f getPosition() const;

    void setSprite(SpriteEnum sprite);
    void hover(bool isHover);

    virtual void setPosition(sf::Vector2f pos);
    virtual void draw(sf::RenderWindow* window) const;
    virtual int activate(
        GemTable& gems, size_t i, size_t j, size_t width, size_t height);
};

#endif