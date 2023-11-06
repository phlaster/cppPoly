#include "headers/game.h"
#include <GL/freeglut.h>
#include <chrono>
#include <thread>

v2 empty = { -1, -1 };

void game::create_field() {
	for (double x = 0; x < game_object::windowSize.x; x += block_size.x) {
		for (double y = game_object::windowSize.y; y >= game_object::windowSize.y / 2; y -= block_size.y) {
			int chance = game_object::create_random((game_object::windowSize.y - y) / block_size.y + 1);
			if (chance == 0) {
				block* p = new block({ x + block_size.x / 2, y - block_size.y / 2 });
			}
		}
	}
}

game* CurrentInstance;

// extern "C"


v2 game::touch(game_object* f, game_object* s) {
    double xOverlap = std::max(0.0, std::min(f->getPos().x + f->getSize().x / 2, s->getPos().x + s->getSize().x / 2) - std::max(f->getPos().x - f->getSize().x / 2, s->getPos().x - s->getSize().x / 2));
    double yOverlap = std::max(0.0, std::min(f->getPos().y + f->getSize().y / 2, s->getPos().y + s->getSize().y / 2) - std::max(f->getPos().y - f->getSize().y / 2, s->getPos().y - s->getSize().y / 2));

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
	if (ball::balls.empty() || win()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		exit(0);
	}
}

void update_balls() {
    ball* to_deleteBall = nullptr;
    for (auto u : ball::balls) {
        u->move();
        if (!u->inGame()) {
            to_deleteBall = u;
        }
    }
    if (to_deleteBall) {
        delete to_deleteBall;
        ball::balls.erase(to_deleteBall);
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
    for (auto u : ball::balls) {
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
    for (auto u : ball::balls) {
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
	ball::drawAllBalls();
	paddle::mainPaddle->drawPaddle();
	glutSwapBuffers();
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	}
	if (key == ' ') {
		for (auto u : ball::balls) {
			if (u->isSticking()) {
				u->notstick();
				u->setSpeed({ 0, ball::normal_speed });
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
	::glutKeyboardFunc(::processNormalKeys);
	::glutReshapeFunc(::resize);
}