#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 100 + 1;
        cout << n << '\n';
        for (int i = 1; i <= n; i++)
        {
            int x1 = rand() % 100, y1 = rand() % 100;
            int x2 = rand() % 100, y2 = rand() % 100;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            if (x1 == x2) x2 += 1;
            if (y1 == y2) y2 += 1;
            cout << x1 + 100 << ' ' << y1 + 100 << ' ' << x2 + 100 << ' ' << y2 + 100 << '\n';
        }
    }
    cout << "0\n";
    return 0;
}
