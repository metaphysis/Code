#include <iostream>

using namespace std;

union
{
    unsigned int byte1;
    unsigned char byte2;           
} block;

int main(int argc, char *argv[])
{
    // 由于union的存放顺序是所有成员都从低地址开始存放，利用该特性就即可
    // 获得CPU对内存是采用Little-endian还是Big-endian模式读写。

    block.byte1 = 1;
    cout << ((block.byte2 == 1) ? "Little-endian\n" : "Big-endian\n");

    return 0;
}
