#ifndef INC_BALL_H
#define INC_BALL_H

#include "Entity.hpp"
#include <set>

class Ball : public Entity {
public:
    static std::set<Ball*> balls;

    Ball(v2 p);
    virtual ~Ball();

    static void initBonuses();
    static void makeShield();
    static void drawAllBalls();
    static double normal_speed;

    virtual bool inGame() const override;
    virtual void move() override;
    virtual v2 getSize() const override;
    void stick();
    void notstick();
    bool isSticking();
    void bounce(Entity* v);

private:
    void drawBall();
    static bool shield;
    bool sticking; 
};

#endif
