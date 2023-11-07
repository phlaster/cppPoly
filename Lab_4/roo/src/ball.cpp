#include "headers/ball.h"
#include "headers/paddle.h"
#include "headers/game.h"
#include <GL/freeglut.h>
#include <climits>
#include <cmath>

std::set<ball*> ball::balls;
bool ball::shield;
double ball::normal_speed;
v2 emp = { -1, -1 };

void ball::initBonuses() {
    shield = false;
}

void ball::makeShield() {
    shield = true;
}

void ball::drawAllBalls() {
    for (auto u : balls) {
        glColor3f(1.0, 0.85, 1.0);
        u->drawBall();
    }
}

void ball::drawBall() {
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

bool ball::inGame() {
    if (pos.y < 0) return false;
    return true;
}

void ball::move() {
    if (sticking) {
        v2 t = paddle::mainPaddle->getPos();
        v2 s = paddle::mainPaddle->getSize();
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

v2 ball::getSize() {
    return { radius * 2.0, radius * 2.0 };
}

void ball::stick() {
    sticking = true;
}

void ball::notstick() {
    sticking = false;
}

void ball::bounce(game_object* v) {
    v2 t = game::touch(this, v);

    double dx = this->getPos().x - v->getPos().x;
    double dy = this->getPos().y - v->getPos().y;
    double angle = atan2(dy, dx);

    double speed = normal_speed + 0.01;

    double sx = speed * cos(angle);
    double sy = speed * sin(angle);

    if (v == paddle::mainPaddle) {
        sy = fabs(sy);
    }

    this->speed = { sx, sy };

    while (game::touch(this, v) != emp) {
        this->move();
    }
}