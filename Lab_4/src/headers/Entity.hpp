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

const v2 ANTIVECTOR = { -1, -1 };


class Entity {
protected:
	v2 pos, speed;
	void drawPoly(int n);
	static double radius; 

public:
	Entity() : pos({ 0, 0 }), speed({ 0, 0 }) {};
	Entity(v2 p) : pos(p), speed({ 0, 0 }) {};
	Entity(v2 p, v2 v) : pos(p), speed(v) {};

	static v2 windowSize;
	
	virtual v2 getSize() const;
	virtual bool inGame() const = 0;
	virtual void move();
	bool touches(const Entity* other) const;

	static void setWindowSize(int W, int H);
	static void setRadius(int r);
	static int create_random(int n);
	
	void setSpeed(v2 s);
	v2 getPos() const;
};
#endif

