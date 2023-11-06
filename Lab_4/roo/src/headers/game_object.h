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


class game_object {
protected:
	v2 pos, speed;
	void drawPoly(int n);
	static int mainTime;
	// static int delay; 
	static int radius; 

public:
	game_object() : pos({ 0, 0 }), speed({ 0, 0 }) {};
	game_object(v2 p) : pos(p), speed({ 0, 0 }) {};
	game_object(v2 p, v2 v) : pos(p), speed(v) {};

	virtual v2 getSize() = 0;
	virtual void move();
	virtual bool inGame() = 0;
		
	static void setWindowSize(int W, int H) {
		windowSize.x = W;
		windowSize.y = H;
	}

	void setSpeed(v2 s) {
		speed = s;
	}
	static void setRadius(int r) {
		radius = r;
	}
	v2 getPos() {
		return pos;
	}
	static void globalClockReset() {
		mainTime = 0;
	}

	static void globalClockTick() {
		mainTime++;
	}

	static v2 windowSize;
	static int create_random(int n);

};
#endif

