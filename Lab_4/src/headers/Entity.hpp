#ifndef INC_GAME_OBJECT_H
#define INC_GAME_OBJECT_H
#include <iostream>
#include <ctime>
#include <chrono>


typedef struct v2 {
    double x;
    double y;

	bool operator==(const v2 &other){
		return (x==other.x && y==other.y);
	}
	bool operator!=(const v2 &other){
		return (x!=other.x || y!=other.y);
	}
} v2;


class Entity {
protected:
	v2 pos, speed;
	void drawPoly(int n);
	static int mainTime;
	static int radius; 

public:
	Entity() : pos({ 0, 0 }), speed({ 0, 0 }) {};
	Entity(v2 p) : pos(p), speed({ 0, 0 }) {};
	Entity(v2 p, v2 v) : pos(p), speed(v) {};

	virtual v2 getSize() = 0;
	virtual void move();
	virtual bool inGame() = 0;
		
	static void setWindowSize(int W, int H);

	void setSpeed(v2 s);
	static void setRadius(int r);
	v2 getPos();
	static void globalClockReset();

	static void globalClockTick();

	static v2 windowSize;
	static int create_random(int n);
};
#endif

