#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 90 + 10;
        cout << n << '\n';
        for (int i = 1; i <= n; i++)
        {
            int bt = rand() % 101;
            int bl = rand() % 101;
            int fl = rand() % 101;
            cout << bt << ' ' << bl << ' ' << fl << '\n';
        }
        int BL = rand() % 6;
        int FL = rand() % 5;
        int BT = 10 - BL - FL;
        cout << BT << ' ' << BL << ' ' << FL << '\n';
    }
    cout << "0\n";

    return 0;
}
