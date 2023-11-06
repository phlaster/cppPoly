#ifndef INC_BALL_H
#define INC_BALL_H
#include "game_object.h"
#include <set>

class ball :
    public game_object
{
public:
    
    static std::set<ball*> balls;

    ball(v2 p) : game_object(p) {
        sticking = true;
        normal_speed = 4;
        bottom = true;
        speed_changing_time = -100000;
        balls.insert(this);
    }

    virtual ~ball() {
        balls.erase(this);
    }

    static void initBonuses();
    static void makeBottom();
    static void drawAllBalls();
    static void changeSpeed();
    static double normal_speed;

    virtual bool isAlife() override;
    virtual void move() override;
    virtual v2 getSize() override;

    void stick();
    void notstick();
    bool isSticking() {
        return sticking;
    }

    void pushOff(game_object* v);

private:

    void drawBall();
    static int speed_changing_time;
    static bool bottom;
    bool sticking; 
};
#endif
