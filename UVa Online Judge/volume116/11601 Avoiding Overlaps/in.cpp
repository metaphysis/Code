#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int T = 100;
    cout << T << '\n';
    for (int cs = 1; cs <= T; cs++)
    {
        int N = 1000;
        cout << N << '\n';
        for (int i = 0; i < N; i++)
        {
            int x1 = rand() % 200 - 100, x2 = rand() % 200 - 100;
            if (x1 > x2) swap(x1, x2);
            if (x1 == x2) x2++;
            int y1 = rand() % 200 - 100, y2 = rand() % 200 - 100;
            if (y1 > y2) swap(y1, y2);
            if (y1 == y2) y2++;
            cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
        }
    }

    return 0;
}
