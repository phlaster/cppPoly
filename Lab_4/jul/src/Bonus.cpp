#include "headers/Bonus.hpp"
#include "headers/Source.hpp"

void PaddleWidthBonus::applyBonus() {
       paddle.setSize(sf::Vector2f(paddle.getSize().x +100, paddle.getSize().y)); // Удваиваем ширину ракетки
      // paddleCurrentWidth = paddle.getSize().x;
       isActive = false;
       timer.restart();

   }

void PaddleWidthBonus::deactive()
{
    sf::Vector2f paddleSize (paddle.getSize().x-100, PADDLE_HEIGHT);
    paddle.setSize(paddleSize);
}

void BallSpeedBonus::deactive()
{
    /*sf::Vector2f ballVelocity = bal.getVelocity();
    sf::Vector2f velocity = sf::Vector2f(ballVelocity.x > 0 ? SPEED : -SPEED, ballVelocity.y > 0 ? SPEED : -SPEED);
    bal.setVelocity(velocity);*/
    ballVelocity /= bonusMultiplier;
 
}

void ChangeDirectionBonus::deactive()
{
    sf::Vector2f ballVelocity = bal.getVelocity();
    sf::Vector2f velocity = sf::Vector2f(-ballVelocity.x, -ballVelocity.y);
    bal.setVelocity(velocity);
    isActive = false;
}

void ExtraLifeBonus::deactive()
{
    line.setFillColor(sf::Color::Transparent);
    isSecondLife = false;
}
