#include "headers/Game.hpp"
#include <iostream>
#include "headers/Source.hpp"
#include <vector>
// #define _USE_MATH_DEFINES
#include <math.h>
using namespace sf;


bool paddledAndBallCollisin(Paddle paddle, sf::CircleShape ball) {
	bool collided =
		ball.getPosition().x >= paddle.shape.getPosition().x - BALL_RADIUS &&
		ball.getPosition().x <= paddle.shape.getPosition().x + paddle.shape.getSize().x + BALL_RADIUS &&
		ball.getPosition().y >= PADDLE_POS_Y - BALL_RADIUS &&
		ball.getPosition().y <= PADDLE_POS_Y - 0.5 * BALL_RADIUS;
	return collided;
}

void Game:: deactiveBonus( std::vector<BonusBall>::iterator it) {
	(*it).bonus->deactive();
	delete (*it).bonus;
	it = bonusBalls.erase(it);
}

void Game::bonusAndPaddleCollusion(std::vector<BonusBall>::iterator it) {
	
}
void Game:: BonusCollision() 
{
	for (auto it = bonusBalls.begin(); it != bonusBalls.end(); ){
		sf::FloatRect ballBonusBounds = (*it).shape.getGlobalBounds();
		ballBonusBounds.left -= 4;
		ballBonusBounds.top -= 4;
		ballBonusBounds.width += 4;
		ballBonusBounds.height += 4;
		float angle = 0.1;
		if (paddledAndBallCollisin(paddle,(*it).shape) ){
			sf::Vector2f pddleSize = paddle.shape.getSize();

			(*it).bonus->applyBonus();
			std::cout << "bonus active" << std::endl;
			int num = std::distance(bonusBalls.begin(), it);
			(*it).shape.setPosition(250 + num * (3 * BONUS_BALL_RADIUS), 15);
		}
		else if ((*it).shape.getPosition().y >= paddle.shape.getPosition().y + 50) {
			delete (*it).bonus;
			it = bonusBalls.erase(it);
		}
		else if ((*it).bonus->isExpired()) {
			deactiveBonus(it);
			std::cout << "its expired" << std::endl;
		}
		else {
			++it;
		}
	}
}
  

void Game::movePaddleAndBall(){	
	double spinBall = SPEED + 0.2;
	if (Keyboard::isKeyPressed(Keyboard::Right))
		if (paddle.shape.getPosition().x < WINDOW_WEIDH - paddle.shape.getSize().x) {
			paddle.shape.move(spinBall, 0);
			if (p == 0)
				ball.shape.move(spinBall, 0);
		}

	if (Keyboard::isKeyPressed(Keyboard::Left))
		if (paddle.shape.getPosition().x > 0) {
			paddle.shape.move(-spinBall, 0);
			if (p == 0)
				ball.shape.move(-spinBall, 0);
		}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		p = 1;
		
	}
}

void Game::moveBall() {
	
	if (ball.shape.getPosition().x < 0 || ball.shape.getPosition().x>WINDOW_WEIDH - BALL_RADIUS) {
		ball.velocity.x = -ball.velocity.x;
	}
	if (ball.shape.getPosition().y < 50) {
		ball.velocity.y = -ball.velocity.y;
	}
	if (paddledAndBallCollisin(paddle, ball.shape)) {

		ball.velocity.y = -ball.velocity.y;
	}
	
}


	




bool Game:: delLife(bool isSecondLife, sf::RectangleShape& extralife) {
	bool answer = false;
	if (ball.shape.getPosition().y > WINDOW_HEIGHT - 10) {
		p = 0;
		if (bonusBalls.size() > 0) {
			for (auto it = bonusBalls.begin(); it != bonusBalls.end();) {
				deactiveBonus(it);
			}
		}
		std::cout << bonusBalls.size() << std::endl;

		ball.shape.setPosition(BALL_POS_X, BALL_POS_Y);
		paddle.shape.setPosition(paddle.getX(), paddle.getY());
		if (isSecondLife) {
			sf::Vector2f paddlesize = sf::Vector2f(PADDLE_WIDTH - (l + 1) * 10 + 10 , PADDLE_HEIGHT);
			paddle.shape.setSize(paddlesize);
			
			extralife.setFillColor(sf::Color::Transparent);
			isSecondLife = false;

		}
		else {
			l++;
			sf::Vector2f paddlesize = sf::Vector2f(PADDLE_WIDTH - (l + 1) * 10, PADDLE_HEIGHT);
			paddle.shape.setSize(paddlesize);
			score--;
			if (l == 3) {
				paddle.shape.setSize(sf::Vector2f(paddlesize));
				ball.shape.setFillColor(Color::Transparent);
				paddle.shape.setFillColor(Color::Transparent);
			}

			answer = true;
		}
	}
	return answer;
}


void Game:: chancecl(int k, sf::RectangleShape& line,  bool& isSecondLife) {
	if (field.isHealthZero(field.blocks[k])) {
		deletedBlocks++;
		score++;
		
		if (0==0) {
			float bonusPosX = field.blocks[k].getPosition().x;
			float bonusPosY = field.blocks[k].getPosition().y;
			sf::CircleShape bonusBall(10);
			bonusBall.setFillColor(sf::Color::White);
			bonusBall.setPosition(bonusPosX, bonusPosY);
			int random = rand() % 5;
			if (random == 0) {
				PaddleWidthBonus* bonus = new PaddleWidthBonus(paddle.shape, 30.0f);
				std::cout << "paddle" << std::endl;
				bonusBalls.push_back(BonusBall(bonusBall, bonus));
			}
			else if (random == 1) {
				BallSpeedBonus* bonus = new BallSpeedBonus(ball.velocity, 1.6, 30.0f, ball);
				std::cout << "slow up" << std::endl;
				bonusBalls.push_back(BonusBall(bonusBall, bonus));
			}
			else if (random == 2) {
				BallSpeedBonus* bonus = new BallSpeedBonus(ball.velocity, 0.4, 30.0f, ball);
				std::cout << "slow down" << std::endl;
				bonusBalls.push_back(BonusBall(bonusBall, bonus));

			}
			else if (random == 3) {
				ExtraLifeBonus* bonus = new ExtraLifeBonus(isSecondLife, line);
				std::cout << "second life" << std::endl;
				bonusBalls.push_back(BonusBall(bonusBall, bonus));

			}
			else if (random == 4) {
				ChangeDirectionBonus* bonus = new ChangeDirectionBonus(ball);
				std::cout << "change direction" << std::endl;
				bonusBalls.push_back(BonusBall(bonusBall, bonus));

			}

		}
		field.blocks.erase(field.blocks.begin() + k);
	}
}

int Game :: delBlock() {
	sf::FloatRect ballBounds = ball.shape.getGlobalBounds();
	ballBounds.left -= 9;
	ballBounds.top -= 9;
	ballBounds.width += 9;
	ballBounds.height += 9;
	float angle = 0.1;
	float angleOffset = 0.1;

	for (unsigned k = 0; k < field.blocks.size(); k++) {
		if (ballBounds.intersects(field.blocks[k].getGlobalBounds()) ) {
			
			sf:: Vector2f velocity = Vector2f(-ball.velocity.x, -ball.velocity.y);
			angle = std::atan2(velocity.y, velocity.x);
			angle += ((rand() % 11) - 5) * M_PI / 180; 
			velocity.x = std::cos(angle) * std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

			Vector2f brickPos = field.blocks[k].getPosition();
			Vector2f ballPos = ball.shape.getPosition();
			float overlapLeft = ball.shape.getPosition().x + ball.shape.getRadius() - brickPos.x;
			float overlapRight = brickPos.x + BLOCK_SIDE - ball.shape.getPosition().x + ball.shape.getRadius();
			float overlapTop = ball.shape.getPosition().y + ball.shape.getRadius() - brickPos.y;
			float overlapBottom = brickPos.y + BLOCK_SIDE - ball.shape.getPosition().y + ball.shape.getRadius();
			bool ballFromLeft(fabs(overlapLeft) < fabs(overlapRight));
			bool ballFromTop(fabs(overlapTop) < fabs(overlapBottom));
			float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
			float minOverlapY = ballFromTop ? overlapTop : overlapBottom;
			std::cout << minOverlapX << " " << minOverlapY <<std:: endl;
			if (minOverlapX < minOverlapY ) {
				if (fabs(minOverlapX) - fabs(minOverlapY) < 1) {
					ball.velocity = Vector2f(velocity.x, velocity.y);
				}
				else if (fabs(minOverlapX) > fabs(minOverlapY)) {
					ball.velocity = Vector2f(-velocity.x, velocity.y);
					std::cout << ballFromLeft << std::endl;
					velocity.x = ballFromLeft ? fabs(velocity.x) : -fabs(velocity.x);
					ball.velocity = Vector2f(velocity.x, -velocity.y);
				
				}
				
					std::cout << ballFromLeft << std::endl;
					velocity.x = ballFromLeft ? -fabs(velocity.x) : fabs(velocity.x);
					ball.velocity = Vector2f(velocity.x, -velocity.y);
				
				
			}
			else if (minOverlapX == minOverlapY) {
				ball.velocity = Vector2f(velocity.x, velocity.y);
			}
			else {
				
				std::cout << ballFromTop << std::endl;
				velocity.y = ballFromTop ? -fabs(velocity.y) : fabs(velocity.y);
				ball.velocity = Vector2f(-velocity.x, velocity.y);
			}
			return k;
		}
	}
	return -1;
}



Game::Game()
{
	score = 0;
	p = 0;
	l = 0;
	std::vector<BonusBall> bonusBalls;
	
}
int Game::start() {
	
	unsigned int windowWidth = WINDOW_WEIDH, windowHeight = WINDOW_HEIGHT;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WEIDH, WINDOW_HEIGHT), "Arcanoid"); 

	sf::RectangleShape extralife;
	Vector2f extraLifeSize(WINDOW_WEIDH, 5);
	extralife.setPosition(0, WINDOW_HEIGHT - 50);
	extralife.setSize(extraLifeSize);
	extralife.setFillColor(sf::Color::Transparent);

	setlocale(LC_ALL, "Russian");

	
	//float paddelCurrentWeigth = PADDLE_WIDTH;
	bool isSecondLife = false;
	

	Font font;
	font.loadFromFile("assets/JetBrainsMono-Medium.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(WINDOW_WEIDH - 150, 10);
	text.setFillColor(Color::White);
	text.setString("Score: " + std::to_string(score));

	std::cout << field.zeroLifeBlocks << std::endl;
	field.generateLife();
	deletedBlocks = field.zeroLifeBlocks;

	sf::Image win;
	win.loadFromFile("assets/win.jpg");
	sf::Texture textureWin;
	textureWin.loadFromImage(win);
	sf::Sprite winSprite;
	winSprite.setTexture(textureWin);
	winSprite.setPosition(WINDOW_WEIDH / 2 - 400, 25);


	sf::Texture textureUnWin;
	textureUnWin.loadFromFile("assets/unwin.jpg");
	sf::Sprite unwinSprite;
	unwinSprite.setTexture(textureUnWin);
	unwinSprite.setPosition(WINDOW_WEIDH / 2 - 400, 25);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
			
				window.close();
		}
		
		Vector2f m = paddle.shape.getPosition();
		if (deletedBlocks != BLOCKS_NUM) {
			movePaddleAndBall();
		}
		else {
			p = 0;
		}

		if (p == 1 && l != 3 && deletedBlocks != BLOCKS_NUM) {
			text.setString("Score: " + std::to_string(score));
			
			moveBall();
			if (bonusBalls.size() > 0) {
				BonusCollision();
			}

			if (delLife(isSecondLife, extralife)) {

				field.delLife();
			}

			int k = delBlock();
			if (k > -1) {
				chancecl(k, extralife, isSecondLife);
			}
			ball.shape.move(ball.velocity);
			
		}
		


		window.clear();
		
		
		for (auto& brick : field.blocks) window.draw(brick);
		for (auto& life : field.lifes) window.draw(life);
		for (auto& bonusBall : bonusBalls) {
			if (bonusBall.shape.getPosition().y > 40){
				bonusBall.shape.move(0, 0.2);
			}
		  
           window.draw(bonusBall.shape);
        }
		window.draw(text);
		
		window.draw(ball.shape);
		window.draw(paddle.shape);
		window.draw(extralife);
		if (p != 1) {
			if (deletedBlocks == BLOCKS_NUM) {
				window.draw(winSprite);
			}
			else if (l == 3) {
				window.draw(unwinSprite);
			}
		}
		
		window.display();
	}
	return 0;
}
