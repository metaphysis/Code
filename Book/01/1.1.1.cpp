#include <iostream>

using namespace std;

union {
    unsigned int bytes;
    unsigned char lowerByte;
} block;

int main(int argc, char *argv[])
{
    block.bytes = 1;
    cout << (block.lowerByte ? "little-endian" : "big-endian") << endl;

    unsigned int bytes = 1;
    cout << (*((char *)(&bytes)) ? "little-endian" : "big-endian") << endl;

    return 0;
}
