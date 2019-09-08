#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000000000;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 1;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 30000 + 1;
        int k = rand() % 10 + 1;
        cout << n << ' ' << k << '\n';
        for (int i = 1; i <= n; i++)
        {
            int x1 = rand() % MAXN, y1 = rand() % MAXN;
            int x2 = rand() % MAXN, y2 = rand() % MAXN;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            if (x1 == x2) x2 += 1;
            if (y1 == y2) y2 += 1;
            cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
        }
    }
    return 0;
}
