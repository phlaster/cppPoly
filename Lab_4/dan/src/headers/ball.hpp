#ifndef INC_BALL_HPP
#define INC_BALL_HPP

#include "game_object.hpp"
#include <set>

class ball : public game_object {
public:
    static std::set<ball*> balls;
    ball(pair_t p) : game_object(p) {
        sticking = true;
        normal_speed = 3.;
        bottom = true;
        speed_changing_time = -100000;
        balls.insert(this);
    }

    ~ball() {
        balls.erase(this);
    }

    static void initBonuses();
    static void makeBottom();
    static void drawAllBalls();
    static void changeSpeed();
    static double normal_speed;

    virtual bool isAlife() override;
    virtual void move() override;
    virtual pair_t getSize() override;

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
