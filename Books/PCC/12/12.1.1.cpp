#include <bits/stdc++.h>

using namespace std;

const int NORTH = 0, NORTH_EAST = 1, EAST = 2, SOUTH_EAST = 3, SOUTH = 4,
    SOUTH_WEST = 5, WEST = 6, NORTH_WEST = 7;

const int CNT_DIRECTIONS = 8;

const int FORWARD = 0, HALF_RIGHT = 1, RIGHT = 2, SHARP_RIGHT = 3,
    BACKWARD = 4, SHARP_LEFT = 5, LEFT = 6, HALF_LEFT = 7;

int offset[8][2] = {
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
};

int main(int argc, char *argv[])
{
    int x, y, direction = NORTH, turn = HALF_RIGHT;

    if (turn == HALF_RIGHT) direction = (direction + 1) % CNT_DIRECTIONS;
    else if (turn == RIGHT) direction = (direction + 2) % CNT_DIRECTIONS;
    else if (turn == HALF_LEFT) direction = (direction + 7) % CNT_DIRECTIONS;
    else if (turn == LEFT) direction = (direction + 6) % CNT_DIRECTIONS;

    x += offset[direction][0], y += offset[directiond][1];

    return 0;
}
