#include <iostream>
#include <bitset>

using namespace std;

int main(int argc, char *argv[])
{
    float f = -12.5;
    
    // 将存储浮点数的四个字节解释为一个无符号整数并输出。
    unsigned int *ui = (unsigned int *)(&f);
    cout << *ui << endl;
    
    // 将无符号整数表示成二进制形式并输出。
    bitset<32> uis(*ui);
    cout << uis.to_string() << endl;
    
    return 0;
}
