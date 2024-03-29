#include "headers/Ball.hpp"
#include "headers/Paddle.hpp"
// #include "headers/GameRunner.hpp"
#include <GL/freeglut.h>
#include <climits>
#include <cmath>

std::set<Ball*> Ball::balls;
bool Ball::shield;
double Ball::normal_speed;

Ball::Ball(v2 p) : Entity(p) {
    sticking = true;
    normal_speed = 4;
    shield = true;
    balls.insert(this);
}
Ball::~Ball() {
    balls.erase(this);
}

void Ball::initBonuses() {
    shield = false;
}

void Ball::makeShield() {
    shield = true;
}

void Ball::drawAllBalls() {
    for (auto u : balls) {
        glColor3f(1.0, 0.85, 1.0);
        u->drawBall();
    }
}

void Ball::drawBall() {
    drawPoly(30);
    if (shield) {
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0, 0);
        glVertex2f(0, 10);
        glVertex2f(600, 10);
        glVertex2f(600, 0);
        glEnd();
    }
}

bool Ball::inGame() const {
    if (pos.y < 0) return false;
    return true;
}

void Ball::move() {
    if (sticking) {
        v2 t = Paddle::mainPaddle->getPos();
        v2 s = Paddle::mainPaddle->getSize();
        pos.x = t.x;
        pos.y = t.y + s.y + radius;
        return;
    }

    if (pos.y + radius > windowSize.y) {
        speed.y = -fabs(speed.y);
    }
    pos.x += speed.x;
    pos.y += speed.y;

    if (pos.x - radius < 0) {
        speed.x *= -1;
        pos.x = radius + 0.5;
    }
    if (pos.x + radius > windowSize.x){
        speed.x *= -1;
        pos.x = windowSize.x - radius - 0.5;
    }

    if (shield && pos.y - radius < 0) {
        speed.y = fabs(speed.y);
        shield = false;
    }
}

v2 Ball::getSize() const {
    double d = 2.0 * radius;
    return { d, d };
}

void Ball::stick() {
    sticking = true;
}

void Ball::notstick() {
    sticking = false;
}
bool Ball::isSticking() {
    return sticking;
}
void Ball::bounce(Entity* surface) {
    double dx = this->getPos().x - surface->getPos().x;
    double dy = this->getPos().y - surface->getPos().y;
    double alpha = std::atan2(dy, dx);
    double speed = normal_speed + 0.01;

    double sx = speed * cos(alpha);
    double sy = speed * sin(alpha);

    if (surface == Paddle::mainPaddle) {
        sy = std::max(fabs(sy), 0.1);
    }

    this->speed = { sx, sy };

    while (this->touches(surface)) {
        this->move();
    }
}