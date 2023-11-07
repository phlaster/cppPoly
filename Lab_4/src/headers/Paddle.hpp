#ifndef INC_PADDLE_H
#define INC_PADDLE_H
#include "Entity.hpp"

class Paddle : public Entity {
public:
    static Paddle* mainPaddle;
    Paddle() :Entity({ 300, 100 }) {
        size = { 80, 10 };
        mainPaddle = this;
        isMagnetic = false;
    }
    void changeSize();
    void drawPaddle();
    void moveLeft();
    void moveRight();
    void stop();
    virtual void move() {}; 
    void magnetize();
    virtual v2 getSize();
    bool isReadyToStick();
    void unMagnit();
    virtual bool inGame();

private:
    v2 size;
    bool isMagnetic;
};

#endif