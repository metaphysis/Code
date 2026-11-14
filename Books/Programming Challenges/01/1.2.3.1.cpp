#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    char c;
    while (cin >> c && c != '*') cout << c;
    cin.unsetf(ios::skipws);
    while (cin >> c && c != '*') cout << c;
    cout << '\n';
    return 0;
}
