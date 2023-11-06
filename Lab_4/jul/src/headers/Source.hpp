#include<cmath>

const float WINDOW_HEIGHT = 900;
const float WINDOW_WEIDH = 1600;

const float BLOCK_SIDE = 50;
const float BLOCKS_IN_COL = 2;
const float BLOCKS_IN_ROW = 4;
const float BLOKS_DISTANCE_X = fabs((WINDOW_WEIDH - (BLOCKS_IN_ROW * BLOCK_SIDE)) / (BLOCKS_IN_ROW + 1));
const float BLOKS_DISTANCE_Y = fabs((WINDOW_HEIGHT - WINDOW_HEIGHT/4 - BLOCK_SIDE - BLOCK_SIDE * BLOCKS_IN_COL) / BLOCKS_IN_COL + 1);
const float BLOCKS_NUM = BLOCKS_IN_ROW * BLOCKS_IN_COL;

const float PADDLE_WIDTH = WINDOW_WEIDH / 4;
const float PADDLE_HEIGHT = 7;
const float PADDLE_POS_X = 1.5 * PADDLE_WIDTH;
const float PADDLE_POS_Y = WINDOW_HEIGHT - 100;


const float BALL_RADIUS = 10;
const float BALL_POS_X = WINDOW_WEIDH / 2 - BALL_RADIUS;
const float BALL_POS_Y = PADDLE_POS_Y - 2 * BALL_RADIUS;

const float SPEED = 0.4;
const float BONUS_BALL_RADIUS = 10;

const double NUM_OF_BALLS = floor((WINDOW_WEIDH - 400) / (2 * BONUS_BALL_RADIUS + 10));