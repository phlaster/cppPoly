#ifndef INC_PADDLE_H
#define INC_PADDLE_H
#include "game_object.hpp"

class paddle : public game_object {
public:
    static paddle* mainPaddle;
    paddle() :game_object({ 300, 100 }) {
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
    bool isReadyToStick() {
        return isMagnetic;
    }
    void unMagnit() {
        isMagnetic = false;
    }
    virtual bool inGame() {
        return true;
    }
private:
    v2 size;
    bool isMagnetic;
};

#endif