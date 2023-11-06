#ifndef INC_BALL_H
#define INC_BALL_H
#include "game_object.h"
#include <set>

class ball : public game_object {
public:
    static std::set<ball*> balls;

    ball(v2 p) : game_object(p) {
        sticking = true;
        normal_speed = 4;
        shield = true;
        balls.insert(this);
    }

    virtual ~ball() {
        balls.erase(this);
    }

    static void initBonuses();
    static void makeShield();
    static void drawAllBalls();
    static double normal_speed;

    virtual bool inGame() override;
    virtual void move() override;
    virtual v2 getSize() override;

    void stick();
    void notstick();
    bool isSticking() {
        return sticking;
    }

    void bounce(game_object* v);

private:

    void drawBall();
    static bool shield;
    bool sticking; 
};
#endif
