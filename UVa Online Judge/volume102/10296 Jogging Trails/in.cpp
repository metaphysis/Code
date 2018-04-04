#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int cases = 1; cases <= 25; cases++)
    {
        int n = rand() % 15 + 2, m = rand() % 500 + n;
        m = min(n * 20, m);
        cout << n << ' ' << m << '\n';
        for (int i = 1; i < n; i++)
            cout << i << ' ' << (i + 1) << ' ' << (rand() % 10000 + 1) << '\n';
        cout << 1 << ' ' << n << ' ' << (rand() % 10000 + 1) << '\n';
        for (int i = n + 1; i <= m; i++)
        {
            int x = rand() % n + 1, y = rand() % n + 1;
            cout << x << ' ' << y << ' ' << (rand() % 10000 + 1) << '\n';
        }
    }
    cout << 0 << '\n';
    return 0;
}
