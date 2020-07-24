#include <bits/stdc++.h>

using namespace std;

void toReadable(string s)
{
    cout << "S = " << s.substr(0, 1);
    cout << " E = " << s.substr(1, 8);
    cout << " T = " << s.substr(9);
}

int main(int argc, char *argv[])
{
    float f = -12.5;

    unsigned int *ui = (unsigned int *)(&f);
    bitset<32> uis(*ui);
    toReadable(uis.to_string());
    cout << endl;

    return 0;
}
