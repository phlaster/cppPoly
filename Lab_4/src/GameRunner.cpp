#include "headers/GameRunner.hpp"
#include "headers/Brick.hpp"
#include "headers/Ball.hpp"
#include "headers/Bonus.hpp"
#include "headers/Paddle.hpp"

#include <GL/freeglut.h>
#include <chrono>
#include <thread>

const Field FIELD = {
    {0,  2,  4,  4,  4,  4,  4,  4,  2,  0},
    {1,  3,  4,  4,  2,  2,  4,  4,  3,  1},
    {1,  5,  3,  3,  3,  3,  3,  3,  5,  1},
    {1,  5,  5,  5,  4,  4,  5,  5,  5,  1},
    {0,  4,  1,  4,  5,  5,  4,  1,  4,  0},
    {0,  4,  4,  4,  1,  1,  4,  4,  4,  0},
    {0,  2,  3,  0,  1,  1,  0,  3,  2,  0},
    {2,  0,  2,  2,  0,  0,  0,  2,  0,  2},
    {1,  2,  0,  1,  0,  0,  1,  0,  2,  1},
    {1,  0,  3,  0,  0,  0,  0,  3,  0,  1},
    {0,  1,  0,  1,  0,  0,  1,  0,  1,  0},
    {1,  0,  0,  0,  0,  0,  0,  0,  0,  1}
};
//     const Field FIELD = { // Break single block and game ends
//         {},{},{},{},{},{},{},{},{},{},{},{},
//     {1,  5,  0,  0,  0,  5,  0,  0,  0,  0}
// };

GameRunner* CurrentInstance;

GameRunner::GameRunner() {
    block_size = { 50, 20 };
    Entity::setWindowSize(600, 600);
    Entity::setRadius(10);
    Brick::setSize(block_size);
    Ball::initBonuses();
    new Ball({ 0, 0 });
    create_field(FIELD);
}

GameRunner::~GameRunner(){
    exit(0);
}

void GameRunner::create_field(const Field& field) {
    double x_0 = 1.5 * block_size.x;
    double dx =  block_size.x;
    double y_0 = Entity::windowSize.y - 2 * block_size.y;
    double dy = block_size.y;

    for (size_t i = 0; i < field.size(); i++) {
        for (size_t j = 0; j < field[i].size(); j++) {
            if (field[i][j] == 0) {
                continue;
            }
            double x = x_0 + j * dx;
            double y = y_0 - i * dy;
            new Brick({x, y}, field[i][j]);
        }
    }
}

void GameRunner::initGame(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Arcanoid!");
	initGlutFunctions();
	glutMainLoop();
}

bool win() {
	bool f = true;
	for (auto u : Brick::blocks) {
		if (u->getHP() != UNDEAD_THRESHOLD) {
			f = false;
			break;
		}
	}
	return f;
}

void endgame_check(){
	if (Ball::balls.empty() || win()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		exit(0);
	}
}

void update_balls() {
    Ball* to_deleteBall = nullptr;
    for (auto ball_i : Ball::balls) {
        ball_i->move();
        if (!ball_i->inGame()) {
            to_deleteBall = ball_i;
        }
    }

    if (to_deleteBall) {
        delete to_deleteBall;
        Ball::balls.erase(to_deleteBall);
    }
}

void update_bonuses() {
    Bonus* to_deleteBonus = nullptr;
    for (Bonus* bonus_i : Bonus::bonuses) {
        bonus_i->move();
        if (bonus_i->touches(Paddle::mainPaddle)) {
            bonus_i->activate();
            to_deleteBonus = bonus_i;
        }
        if (!bonus_i->inGame()) {
            to_deleteBonus = bonus_i;
        }
    }
    if (to_deleteBonus) {
        delete to_deleteBonus;
        Bonus::bonuses.erase(to_deleteBonus);
    }
}

void handle_ball_paddle_collisions() {
    for (Ball* ball_i : Ball::balls) {
        if (!ball_i->isSticking() && ball_i->touches(Paddle::mainPaddle)) {
            if (Paddle::mainPaddle->isReadyToStick()) {
                Paddle::mainPaddle->unMagnit();
                ball_i->stick();
                ball_i->setSpeed({ 0, 0 });
                continue;
            }
            ball_i->bounce(Paddle::mainPaddle);
        }
    }
}

void handle_ball_block_collisions() {
    Brick* to_deleteBlock = nullptr;
    for (Ball* ball_i : Ball::balls) {
        for (Brick* brick_j : Brick::blocks) {
            if (ball_i->touches(brick_j)) {
                brick_j->loose_hp();
                if (!brick_j->inGame()) {
                    to_deleteBlock = brick_j;
                }
                ball_i->bounce(brick_j);
            }
        }
    }
    if (to_deleteBlock) {
        delete to_deleteBlock;
        Brick::blocks.erase(to_deleteBlock);
    }
}

void GameRunner::theLogic() {
    endgame_check();
    update_balls();
    update_bonuses();
    handle_ball_paddle_collisions();
    handle_ball_block_collisions();
}

void renderScene() {
    glClearColor(0.18, 0.15, 0.36, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double w = glutGet(GLUT_WINDOW_WIDTH);
	double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, 0, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CurrentInstance->theLogic();
	Brick::drawAllBlocks();
	Bonus::drawAllBonuses();
	Ball::drawAllBalls();
	Paddle::mainPaddle->drawPaddle();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keypress(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	}
	if (key == ' ') {
		for (auto ball_i : Ball::balls) {
			if (ball_i->isSticking()) {
				ball_i->notstick();
				ball_i->setSpeed({ 0, Ball::normal_speed });
			}
		}
	}
	if (key == 'a') {
		Paddle::mainPaddle->moveLeft();
	} else if (key == 'd') {
		Paddle::mainPaddle->moveRight();
    }
}

void resize(int w, int h) {
	glViewport(0, 0, w, h);
}

void GameRunner::initGlutFunctions() {
	CurrentInstance = this;
	::glutDisplayFunc(::renderScene);
	::glutIdleFunc(::renderScene);
	::glutKeyboardFunc(::keypress);
	::glutReshapeFunc(::resize);
}
