#ifndef INC_PADDLE_H
#define INC_PADDLE_H
#include "Entity.hpp"

class Paddle : public Entity {
public:
    static Paddle* mainPaddle;
    Paddle();
    virtual void move() override {}; 
    virtual v2 getSize() const override;
    virtual bool inGame() const override;
    
    void changeSize();
    void drawPaddle();
    void moveLeft();
    void moveRight();
    void stop();
    void magnetize();
    bool isReadyToStick();
    void unMagnit();

private:
    v2 size;
    bool isMagnetic;
};

#endif