#include <iostream>

using namespace std;

const int NORTH = 0, SOUTH = 1, WEST = 2, EAST = 3, NORTH_WEST = 4,
    NORTH_EAST = 5, SOUTH_WEST = 6, SOUTH_EAST = 7;
    
const int LEFT = 0, RIGHT = 1, FORWARD = 2, BACKWARD = 3, SHARP_LEFT = 4,
    HALF_LEFT = 5, SHARP_RIGHT = 6, HALF_RIGHT = 7;

int directions[8][8] = { 
    {WEST, EAST, NORTH, SOUTH, SOUTH_WEST, NORTH_WEST, SOUTH_EAST, NORTH_EAST},
    {EAST, WEST, SOUTH, NORTH, NORTH_EAST, SOUTH_EAST, NORTH_WEST, SOUTH_WEST},
    {SOUTH, NORTH, WEST, EAST, SOUTH_EAST, SOUTH_WEST, NORTH_EAST, NORTH_WEST}, 
    {NORTH, SOUTH, EAST, WEST, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST},
    {SOUTH_WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH, WEST, EAST, NORTH},
    {NORTH_WEST, SOUTH_EAST, NORTH_EAST, SOUTH_WEST, WEST, NORTH, SOUTH, EAST},
    {SOUTH_EAST, NORTH_WEST, SOUTH_WEST, NORTH_EAST, EAST, SOUTH, NORTH, WEST},
    {NORTH_EAST, SOUTH_WEST, SOUTH_EAST, NORTH_WEST, NORTH, EAST, WEST, SOUTH}
};

int offset[8][8][2] = {
    {{-1, 0}, {+1, 0}, {0, +1}, {0, -1}, {-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}},
    {{+1, 0}, {-1, 0}, {0, -1}, {0, +1}, {+1, +1}, {+1, -1}, {-1, +1}, {-1, -1}},
    {{0, -1}, {0, +1}, {-1, 0}, {+1, 0}, {+1, -1}, {-1, -1}, {+1, +1}, {-1, +1}},
    {{0, +1}, {0, -1}, {+1, 0}, {-1, 0}, {-1, +1}, {+1, +1}, {-1, -1}, {+1, -1}},
    {{-1, -1}, {+1, +1}, {-1, +1}, {+1, -1}, {0, -1}, {-1, 0}, {+1, 0}, {0, +1}},
    {{-1, +1}, {+1, -1}, {+1, +1}, {-1, -1}, {-1, 0}, {0, +1}, {0, -1}, {+1, 0}},
    {{+1, -1}, {-1, +1}, {-1, -1}, {+1, +1}, {+1, 0}, {0, -1}, {0, +1}, {-1, 0}},
    {{+1, +1}, {-1, -1}, {+1, -1}, {-1, +1}, {0, +1}, {+1, 0}, {-1, 0}, {0, -1}}
};

int main(int argc, char *argv[])
{
    
    return 0;
}
