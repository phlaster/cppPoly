#pragma once
#include "Field.hpp"
#include "Bonus.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include <memory>



class Game {
private:
	
	sf::RenderWindow window;
	int deletedBlocks = 0;
	int score;
	int p;
	int l;
	std::vector<BonusBall> bonusBalls;
	Field field;
	Paddle paddle;
	Ball ball;

public:
	
	
	int delBlock();
	void chancecl(int k, sf::RectangleShape& line, bool& isSecondLife);
	bool delLife(bool isSecondLife, sf::RectangleShape& extralife);
	void moveBall();
	void movePaddleAndBall();
	void BonusCollision();
	void bonusAndPaddleCollusion(std::vector<BonusBall>::iterator it);
	void deactiveBonus( std::vector<BonusBall>::iterator it);
	void gameLogic();
	Game();
	~Game() {};
	int start();
};