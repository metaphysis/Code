#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++)
    {
        int w = rand() % 100 + 1;
        int n;
        if (w == 100) n = 100;
        else
        {
            n = w + rand() % (100 - w) + 1;
        }
        cout << n << ' ' << w << '\n';
        for (int i = 1; i <= n; i++)
        {
            if (i > 1) cout << ' ';
            cout << rand() % 10000 + 1;
        }
        cout << '\n';
    }
    return 0;
}
