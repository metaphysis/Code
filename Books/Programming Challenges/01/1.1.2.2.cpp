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
    float f1 = 123456789.0, f2 = 1234567.0;

    unsigned int *ui1 = (unsigned int *)(&f1);
    bitset<32> uis1(*ui1);
    cout << "original value: 123456789.0" << '\n';
    cout << "stored value: " << fixed << f1 << '\n';
    toReadable(uis1.to_string());
    cout << "\n\n";

    unsigned int *ui2 = (unsigned int *)(&f2);
    bitset<32> uis2(*ui2);
    cout << "original value: 1234567.0" << endl;
    cout << "stored value: " << fixed << f2 << '\n';
    toReadable(uis2.to_string());
    cout << '\n';

    return 0;
}
