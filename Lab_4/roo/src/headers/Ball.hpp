#ifndef INC_BALL_H
#define INC_BALL_H

#include "game_object.hpp"
#include <set>

class Ball : public game_object {
public:
    static std::set<Ball*> balls;

    Ball(v2 p);
    virtual ~Ball();

    static void initBonuses();
    static void makeShield();
    static void drawAllBalls();
    static double normal_speed;

    virtual bool inGame() override;
    virtual void move() override;
    virtual v2 getSize() override;
    void stick();
    void notstick();
    bool isSticking();
    void bounce(game_object* v);

private:
    void drawBall();
    static bool shield;
    bool sticking; 
};

#endif
