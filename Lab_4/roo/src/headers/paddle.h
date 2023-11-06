#ifndef INC_PADDLE_H
#define INC_PADDLE_H
#include "game_object.h"

class paddle : public game_object {
public:
    static paddle* mainPaddle;
    paddle() :game_object({ 300, 100 }) {
        size = { 80, 10 };
        change_size_time = -100000;
        mainPaddle = this;
        to_stick = false;
    }
    void changeSize();
    void drawPaddle();
    void moveLeft();
    void moveRight();
    virtual void move() {}; 
    void activateSticking();
    virtual v2 getSize();
    bool isReadyToStick() {
        return to_stick;
    }
    void notReadyToStick() {
        to_stick = false;
    }
    virtual bool inGame() {
        return true;
    }
private:
    v2 size;
    int change_size_time;
    bool to_stick;
};

#endif