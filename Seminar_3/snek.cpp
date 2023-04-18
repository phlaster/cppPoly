// Limited functional
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

bool gameOver;
const int width = 50;
const int height = 25;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    clear(); // clear the screen

    // draw the top border
    for (int i = 0; i < width + 2; i++)
        printw("#");
    printw("n");

    // draw the game board
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                printw("#");
            if (i == y && j == x)
                printw("O");
            else if (i == fruitY && j == fruitX)
                printw("F");
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printw("o");
                        print = true;
                    }
                }
                if (!print)
                    printw(" ");
            }

            if (j == width - 1)
                printw("#");
        }
        printw("n");
    }

    // draw the bottom border
    for (int i = 0; i < width + 2; i++)
        printw("#");
    printw("n");

    // display the score
    printw("Score: %dn", score);
    refresh(); // update the screen
}

void Input()
{
    switch (getch())
    {
    case 'a':
        dir = LEFT;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'w':
        dir = UP;
        break;
    case 's':
        dir = DOWN;
        break;
    case 'x':
        gameOver = true;
        break;
    }
}

void Logic()
{
    // update the tail positions
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // update the head position
    switch (dir)
    {
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
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // check for collision with the fruit
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    srand(time(NULL)); // seed the random number generator
    initscr(); // initialize ncurses
    noecho(); // don't echo keyboard input
    curs_set(0); // hide the cursor
    keypad(stdscr, TRUE); // enable function keys
    nodelay(stdscr, TRUE); // don't wait for keyboard input
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        usleep(90000); // pause for a short time to slow down the game
    }
    endwin(); // clean up ncurses
    return 0;
}
