#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int T = 100;
    cout << T << "\n\n";
    for (int cs = 1; cs <= T; cs++)
    {
        long long k, N, S, D, x, y;
        k = rand() % 100000000;
        if (rand() % 100 > 70) k *= -1;
        N = rand() % 1000 + 1;
        S = rand() % 1000 + 1;
        D = rand() % 1000000000 + 1;
        cout << k << ' ' << N << ' ' << S << ' ' << D << '\n';
        for (int i = 0; i < N; i++)
        {
            x = rand() % 100000000;
            if (rand() % 100 > 70) x *= -1;
            y = k + rand() % (100000000LL - k);
            cout << x << ' ' << y << '\n';
        }
        cout << '\n';
    }

    return 0;
}
