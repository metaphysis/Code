#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    char sentence[] = "the quick brown fox jumps over the lazy dog.";
    memset(sentence, '-', 4);	// 将给定字符串的前四个字符修改为连字符‘-’。
    cout << sentence << endl;

    return 0;
}
