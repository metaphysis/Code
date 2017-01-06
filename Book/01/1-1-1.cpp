#include <iostream>

using namespace std;

union {
    unsigned int dWord;
    unsigned char byte;
} block;

int main(int argc, char *argv[])
{
    // 第一种方式：利用union的特性，将block的第一个成员赋值为1，然后获取内存
    // 低位字节的值，如果是小端序，则低位字节存储的值为1，若为大端序，则值为0。
    block.dWord = 1;
    cout << (block.byte ? "little-endian" : "big-endian") << endl;

    // 第二种方式：利用指针直接获取第一个字节的值。
    unsigned int dWord = 1;
    cout << (*((char *)(&dWord)) ? "little-endian" : "big-endian") << endl;

    return 0;
}
