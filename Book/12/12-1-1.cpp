#include <iostream>

using namespace std;

const int NORTH = 0, NORTH_EAST = 1, EAST = 2, SOUTH_EAST = 3, SOUTH = 4,
    SOUTH_WEST = 5, WEST = 6, NORTH_WEST = 7;
    
const int FORWARD = 0, HALF_RIGHT = 1, RIGHT = 2, SHARP_RIGHT = 3,
    BACKWARD = 4, SHARP_LEFT = 5, LEFT = 6, HALF_LEFT = 7;

int offset[8][2] = {
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
};

int main(int argc, char *argv[])
{
    
    return 0;
}
