#include <bits/stdc++.h>

using namespace std;

void displayBits(int n, int b, int i)
{
    cout << "n = " << (bitset<32>(n)).to_string() << endl;
    for (int j = 0; j < (36 - i - 1); j++) cout << ' '; cout << '^' << endl;
    cout << "b = " << (bitset<32>(b)).to_string() << endl;
}

int main(int argc, char *argv[])
{
    int n = 19820624, b = 0, i = 6;

    b = (n & (0x1 << i)) >> i; displayBits(n, b, i);
    b = n | (0x1 << i); displayBits(n, b, i);
    b = n & (~(0x1 << i)); displayBits(n, b, i);
    b = n ^ (0x1 << i); displayBits(n, b, i);
    b = n & (-n); displayBits(n, b, i);

    return 0;
}
