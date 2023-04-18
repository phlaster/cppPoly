#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

class SnakeGame {
public:
    SnakeGame(int w, int h) : width(w), height(h), x(w/2), y(h/2), fruitX(0), fruitY(0), score(0), nTail(0), dir(STOP), gameOver(false) {
        tailX = new int[width*height];
        tailY = new int[width*height];
        Setup();
    }

    ~SnakeGame() {
        delete[] tailX;
        delete[] tailY;
    }

    void Run() {
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            usleep(150000 - score*4000); // Game speed increases
        }
    }

private:
    int width, height;
    int x, y, fruitX, fruitY, score;
    int *tailX, *tailY;
    int nTail;
    bool gameOver;
    bool tastyFruit = false;
    int frutCounter = 1;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

    void Setup() {
        srand(time(NULL)); // seed the random number generator
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

    void Draw() {
        clear(); // clear the screen
        // draw the top border
        for (int i = 0; i < width + 2; i++)
            printw("=");
        printw(" ");

        // draw the game board
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    printw("|");
                if (i == y && j == x)
                    printw("@");
                else if (i == fruitY && j == fruitX)
                    if (tastyFruit) printw("T");
                    else printw("+");
                else {
                    bool print = false;
                    for (int k = 0; k < nTail; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            printw("o");
                            print = true;
                        }
                    }
                    if (!print)
                        printw(" ");
                }
                if (j == width - 1)
                    printw("|");
            }
            printw(" ");
        }

        // draw the bottom border
        for (int i = 0; i < width + 2; i++)
            printw("=");
        printw(" ");

        // display the score
        printw("Score: %d", score);
        refresh(); // update the screen
    }

    void Input() {
        switch (getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }

    void Logic() {
        // update the tail positions
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < nTail; i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        // update the head position
        switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
        }

        // check for collision with the walls
        if (x < 0 || x >= width || y < 0 || y >= height)
            gameOver = true;

        // check for collision with the tail
        for (int i = 0; i < nTail; i++) {
            if (tailX[i] == x && tailY[i] == y)
                gameOver = true;
        }

        // check for collision with the fruit
        if (x == fruitX && y == fruitY) {
            if (tastyFruit)
            {
                score += 2;
                nTail++;
                tastyFruit = false;
            }
            else
            {
                score += 1;
            }
            frutCounter = (frutCounter+1)%5;
            fruitX = rand() % width;
            fruitY = rand() % height;
            if (frutCounter==0) tastyFruit = true;
            nTail++;
        }
    }
};

int main() {
    initscr(); // initialize ncurses
    noecho(); // don't echo keyboard input
    curs_set(0); // hide the cursor
    keypad(stdscr, TRUE); // enable function keys
    nodelay(stdscr, TRUE); // don't wait for keyboard input
    SnakeGame game(50, 25);
    game.Run();
    endwin(); // clean up ncurses
    return 0;
}
