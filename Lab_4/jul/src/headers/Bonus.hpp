#pragma once
#include "Paddle.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ball.hpp"



class Bonus {
protected:
    sf::Clock timer;

public:
    virtual void applyBonus() = 0;
    virtual bool isExpired() = 0;
    virtual void deactive()=0;
   
};

class PaddleWidthBonus : public Bonus {
private:
    sf::RectangleShape& paddle;
    float originalWidth;
    float bonusDuration;
    //float& paddleCurrentWidth;
    bool isActive = false;

public:
    PaddleWidthBonus(sf::RectangleShape& paddle, float bonusDuration)
        : paddle(paddle), bonusDuration(bonusDuration) {
        originalWidth = paddle.getSize().x;
    }

    void applyBonus() override;

    bool isExpired() override {
        return timer.getElapsedTime().asSeconds() >= bonusDuration;
    }
    void deactive() override;
};
class BallSpeedBonus : public Bonus {
private:
    sf::Vector2f& ballVelocity;
    float bonusMultiplier;
    float bonusDuration;
    bool isActive = false;
    Ball& bal;

public:
    BallSpeedBonus(sf::Vector2f& ballVelocity, float bonusMultiplier, float bonusDuration, Ball& ball)
        : ballVelocity(ballVelocity), bonusMultiplier(bonusMultiplier), bonusDuration(bonusDuration), bal(ball) {}

    void applyBonus() override {
        // Customize the bonus effect here, such as increasing the ball speed
        ballVelocity *= bonusMultiplier;
        isActive = true;
        timer.restart();
    }
    void deactive() override;
    bool isExpired() override {
            return timer.getElapsedTime().asSeconds() >= bonusDuration;
    }
};
class BonusBall {
public:
    sf::CircleShape shape;
    Bonus* bonus;  // Указатель на бонус, соответствующий шарику
    ~BonusBall() {};

    BonusBall(const sf::CircleShape& shape, Bonus* bonus)
        : shape(shape), bonus(bonus) {}
};

class ExtraLifeBonus : public Bonus {

public:
    bool& isSecondLife;
    sf::RectangleShape& line;
    bool isActive = false;

    ExtraLifeBonus(bool& isSecondLife, sf::RectangleShape& line)
        : isSecondLife(isSecondLife), line(line){}

    void applyBonus() override {
        line.setFillColor(sf::Color::Red);
        isSecondLife = true;
        timer.restart();
        isActive = true;
    }

    bool isExpired() override {
        return false;// This bonus doesn't expire
    }
    void deactive() override;
};

class ChangeDirectionBonus : public Bonus {
public:
    //sf::Vector2f& ballVelocity;
    //sf::CircleShape& ball;
    bool isActive = false;
    float time = 5+rand()%10;
    Ball bal;

    ChangeDirectionBonus(Ball& ball)
        :bal(ball){}

    void applyBonus() override {
        isActive = true;
        timer.restart();
    }

    bool isExpired() override {
        if (isActive && timer.getElapsedTime().asSeconds() >= time) {
            
            isActive = false;
            return true;
        }
        return false;
    }

    void deactive() override;
};


