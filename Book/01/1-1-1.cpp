#include <iostream>

using namespace std;

union
{
    unsigned int word;
    unsigned char byte;           
} block;

int main(int argc, char *argv[])
{
    // 利用联合的特性，将联合的第一个成员赋值为1，然后获取内存低位字节的值，
    // 如果是小端序，则低位字节存储的值为1，若为大端序，则值为0。
    block.word = 1;
    cout << (block.byte ? "little-endian\n" : "big-endian\n");

    return 0;
}
