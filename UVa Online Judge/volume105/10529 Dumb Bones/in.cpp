#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 1000 + 1;
        int S = rand() % 500 + 1;
        int pl = rand() % S;
        int pr = S - pl;
        cout << n << ' ' << pl / 1000.0 << ' ' << pr / 1000.0 << '\n';
    }
    cout << 0 << '\n';
    return 0;
}
