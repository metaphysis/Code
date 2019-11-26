#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    float f = -12.5;
    unsigned int *ui = (unsigned int *)(&f);
    bitset<32> uis(*ui);
    cout << uis.to_string() << endl;
    return 0;
}
