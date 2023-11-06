#ifndef INC_SLIDE_HPP
#define INC_SLIDE_HPP
#include "game_object.hpp"

class slide :
    public game_object
{
public:
    static slide* mainSlide;
    slide() :game_object({ 300, 100 }) {
        size = { 80, 10 };
        change_size_time = -100000;
        mainSlide = this;
        to_stick = false;
    }
    void changeSize();
    void drawSlide();
    void moveLeft();
    void moveRight();
    virtual void move() {};
    void activateSticking();
    virtual pair_t getSize();
    bool isReadyToStick() {
        return to_stick;
    }
    void notReadyToStick() {
        to_stick = false;
    }
    virtual bool isAlife() {
        return true;
    }
private:
    pair_t size;
    int change_size_time;
    bool to_stick;
};

#endif