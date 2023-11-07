#include "headers/game.hpp"
#include "headers/block.hpp"
#include <GL/freeglut.h>
#include <chrono>
#include <thread>
#include <vector>

v2 empty = { -1, -1 };

game::game() {
    block_size = { 50, 20 };
    game_object::setWindowSize(600, 600);
    game_object::globalClockReset();
    game_object::setRadius(10);
    block::setSize(block_size);
    Ball::initBonuses();
    Ball* p = new Ball({ 0, 0 });
    Ball::balls.insert(p);
    create_field();
}

game::~game(){
    exit(0);
}
void game::create_field() {
    std::vector<std::vector<int>> field = {
        {5,  2,  4,  4,  4,  4,  4,  4,  2,  5},
        {5,  3,  4,  4,  2,  2,  4,  4,  3,  5},
        {5,  4,  3,  3,  3,  3,  3,  3,  4,  5},
        {5,  5,  5,  5,  5,  5,  5,  5,  5,  5},
        {0,  4,  1,  4,  0,  0,  4,  1,  4,  0},
        {0,  4,  4,  4,  1,  1,  4,  4,  4,  0},
        {0,  2,  3,  1,  1,  1,  1,  3,  2,  0},
        {2,  2,  2,  2,  0,  0,  2,  2,  2,  2},
        {1,  0,  0,  1,  0,  0,  1,  0,  0,  1},
        {1,  3,  3,  3,  0,  0,  3,  3,  3,  1},
        {1,  1,  5,  5,  0,  0,  5,  5,  1,  1},
        {1,  0,  0,  0,  0,  0,  0,  0,  0,  1}
    };
    //     std::vector<std::vector<int>> field = {
    //         {},{},{},{},{},{},{},{},{},{},{},{},
    //     {1,  5,  0,  0,  0,  5,  0,  0,  0,  0}
    // };
    double x_0 = 1.5 * block_size.x;
    double dx =  block_size.x;
    double y_0 = game_object::windowSize.y - 2 * block_size.y;
    double dy = block_size.y;

    for (size_t i = 0; i < field.size(); i++) {
        for (size_t j = 0; j < field[i].size(); j++) {
            if (field[i][j] == 0) {
                continue;
            }

            double x = x_0 + j * dx;
            double y = y_0 - i * dy;

            block* new_block = new block({x, y}, field[i][j]);
        }
    }
}


game* CurrentInstance;

v2 game::touch(game_object* f, game_object* s) {
    double xOverlap = std::max(
        0.0,
        std::min(f->getPos().x + f->getSize().x / 2, s->getPos().x + s->getSize().x / 2) -
        std::max(f->getPos().x - f->getSize().x / 2, s->getPos().x - s->getSize().x / 2)
    );
    double yOverlap = std::max(
        0.0,
        std::min(f->getPos().y + f->getSize().y / 2, s->getPos().y + s->getSize().y / 2) -
        std::max(f->getPos().y - f->getSize().y / 2, s->getPos().y - s->getSize().y / 2)
    );

    if (xOverlap > 0 && yOverlap > 0) {
        return { xOverlap, yOverlap };
    }
    return { -1, -1 };
}
void game::initGame(int argc, char** argv) {
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
	for (auto u : block::blocks) {
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
    for (auto u : Ball::balls) {
        u->move();
        if (!u->inGame()) {
            to_deleteBall = u;
        }
    }
    if (to_deleteBall) {
        delete to_deleteBall;
        Ball::balls.erase(to_deleteBall);
    }
}

void update_bonuses() {
    bonus* to_deleteBonus = nullptr;
    for (auto u : bonus::bonuses) {
        u->move();
        if (!u->inGame()) {
            to_deleteBonus = u;
        }
    }
    if (to_deleteBonus) {
        delete to_deleteBonus;
        bonus::bonuses.erase(to_deleteBonus);
    }
}

void handle_ball_paddle_collisions() {
    for (auto u : Ball::balls) {
        if (!u->isSticking() && game::touch(u, paddle::mainPaddle) != empty) {
            if (paddle::mainPaddle->isReadyToStick()) {
                paddle::mainPaddle->unMagnit();
                u->stick();
                u->setSpeed({ 0, 0 });
                continue;
            }
            u->bounce(paddle::mainPaddle);
        }
    }
}

void handle_bonus_paddle_collisions() {
    bonus* to_deleteBonus = nullptr;
    for (auto u : bonus::bonuses) {
        if (game::touch(u, paddle::mainPaddle) != empty) {
            u->activate();
            to_deleteBonus = u;
        }
    }
    if (to_deleteBonus) {
        delete to_deleteBonus;
        bonus::bonuses.erase(to_deleteBonus);
    }
}

void handle_ball_block_collisions() {
    block* to_deleteBlock = nullptr;
    for (auto u : Ball::balls) {
        for (auto v : block::blocks) {
            if (game::touch(u, v) != empty) {
                v->touch();
                if (!v->inGame()) {
                    to_deleteBlock = v;
                }
                u->bounce(v);
            }
        }
    }
    if (to_deleteBlock) {
        delete to_deleteBlock;
        block::blocks.erase(to_deleteBlock);
    }
}

void game::theLogic() {
    endgame_check();
    game_object::globalClockTick();
    update_balls();
    update_bonuses();
    handle_ball_paddle_collisions();
    handle_bonus_paddle_collisions();
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
	block::drawAllBlocks();
	bonus::drawAllBonuses();
	Ball::drawAllBalls();
	paddle::mainPaddle->drawPaddle();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keypress(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	}
	if (key == ' ') {
		for (auto u : Ball::balls) {
			if (u->isSticking()) {
				u->notstick();
				u->setSpeed({ 0, Ball::normal_speed });
			}
		}
	}
	if (key == 'a' || key == 'A') {
		paddle::mainPaddle->moveLeft();
	} else if (key == 'd' || key == 'D') {
		paddle::mainPaddle->moveRight();
	}
}

void resize(int w, int h) {
	glViewport(0, 0, w, h);
}

void game::initGlutFunctions() {
	CurrentInstance = this;
	::glutDisplayFunc(::renderScene);
	::glutIdleFunc(::renderScene);
	::glutKeyboardFunc(::keypress);
	::glutReshapeFunc(::resize);
}