#ifndef INC_GAME_OBJECT_HPP
#define INC_GAME_OBJECT_HPP

#include <iostream>
#include <ctime>
#include <chrono>
#include <GL/freeglut.h>

#define pair_t std::pair<double, double>
#define x first
#define y second

using namespace std::chrono;

class game_object
{
public:
	game_object() : pos({ 0, 0 }), speed({ 0, 0 }) {};
	game_object(pair_t p) : pos(p), speed({ 0, 0 }) {};
	game_object(pair_t p, pair_t v) : pos(p), speed(v) {};

	static void setWindowSize(int W, int H) {
		windowSize.x = W;
		windowSize.y = H;
	}

	void setSpeed(pair_t s) {
		speed = s;
	}
	virtual pair_t getSize() = 0;
	virtual void move();
	virtual bool isAlife() = 0;
	static void setRadius(int r) {
		radius = r;
	}
	pair_t getPos() {
		return pos;
	}
	static void setDealay(int d) {
		delay = d;
	}

	static void setMainTime() {
		mainTime = 0;
	}

	static void apdateMainTime() {
		mainTime++;
	}

	static pair_t windowSize;
	static int create_random(int n);

protected:
	pair_t pos, speed;
	void drawNGon(int n);
	static int mainTime;
	static int delay; //the time of bonuses application
	static int radius; //for ball and bonus
};
#endif

