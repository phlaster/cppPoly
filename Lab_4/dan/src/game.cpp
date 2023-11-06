#include "headers/game.hpp"
#include <chrono>
#include <thread>


pair_t empty = { -1, -1 };

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


pair_t game::touch(game_object* f, game_object* s) {
	double X, Y;
	if (f->getPos().x > s->getPos().x) std::swap(f, s);
	if (f->getPos().x + f->getSize().x / 2 >= s->getPos().x - s->getSize().x / 2) {
		X = f->getPos().x + +f->getSize().x / 2 - s->getPos().x - s->getSize().x / 2;
		
		if (f->getPos().y > s->getPos().y) std::swap(f, s);
		if (f->getPos().y + f->getSize().y / 2 >= s->getPos().y - s->getSize().y / 2) {
			Y = f->getPos().y + f->getSize().y / 2 - s->getPos().y - s->getSize().y / 2;
			return { X, Y };
		}
	}
	return { -1, -1 };
}

void game::initGame(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Arcanoid");

	initGlutFunctions();

	glutMainLoop();
}

bool win() {
	bool f = true;
	for (auto u : block::blocks) {
		if (u->getHP() != absolut) {
			f = false;
			break;
		}
	}
	return f;
}

void game::mechanic() {
	if (ball::balls.empty() || win()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		exit(0);
	}
	game_object::apdateMainTime();
	ball* to_deleteBall = NULL;
	for (auto u : ball::balls) {
		u->move();
		if (to_deleteBall) {
			delete to_deleteBall;
			to_deleteBall = NULL;
		}
		if (!u->isAlife()) {
			to_deleteBall = u;
		}
	}
	if (to_deleteBall) delete to_deleteBall;

	bonus* to_deleteBonus = NULL;
	for (auto u : bonus::bonuses) {
		u->move();
		if (to_deleteBonus) {
			delete to_deleteBonus;
			to_deleteBonus = NULL;
		}
		if (!u->isAlife()) {
			to_deleteBonus = u;
		}
	}
	if (to_deleteBonus) delete to_deleteBonus;

	for (auto u : ball::balls) {
		if (!u->isSticking() && touch(u, slide::mainSlide) != empty) {
			if (slide::mainSlide->isReadyToStick()) {
				slide::mainSlide->notReadyToStick();
				u->stick();
				u->setSpeed({ 0, 0 });
				continue;
			}
			u->pushOff(slide::mainSlide);
		}
	}
	to_deleteBonus = NULL;
	for (auto u : bonus::bonuses) {
		if (to_deleteBonus) {
			delete to_deleteBonus;
			to_deleteBonus = NULL;
		}
		if (touch(u, slide::mainSlide) != empty) {
			u->activate();
			to_deleteBonus = u;
		}
	}

	block* to_deleteBlock = NULL;
	for (auto u : ball::balls) {
		for (auto v : block::blocks) {
			if (to_deleteBlock) {
				delete to_deleteBlock;
				to_deleteBlock = NULL;
			}
			if (touch(u, v)!=empty) {
				v->touch();
				if (!v->isAlife()) {
					to_deleteBlock = v;
				}
				u->pushOff(v);
			}
		}
	}
	if (to_deleteBlock) delete to_deleteBlock;
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
	CurrentInstance->mechanic();
	block::drawAllBlocks();
	bonus::drawAllBonuses();
	ball::drawAllBalls();
	slide::mainSlide->drawSlide();
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
		slide::mainSlide->moveLeft();
	} else if (key == 'd' || key == 'D') {
		slide::mainSlide->moveRight();
	}
	
}
void resize(int w, int h) {
	glViewport(0, 0, 600, 600);
}

void game::initGlutFunctions() {
	CurrentInstance = this;
	::glutDisplayFunc(::renderScene);
	::glutIdleFunc(::renderScene);
	::glutKeyboardFunc(::processNormalKeys);
	::glutReshapeFunc(::resize);
}