// Integral Determinant
// UVa ID: 684
// Verdict: Accepted
// Submission Date: 2021-12-01
// UVa Run Time: 0.020s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
long long g[32][32];

long long determinant()
{
    long long r = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int x = i, y = j;
            while (g[y][i])
            {
                long long q = g[x][i] / g[y][i];
                for (int k = i; k < n; k++) g[x][k] -= g[y][k] * q;
                swap(x, y);
            }
            if (x != i)
            {
                swap(g[i], g[j]);
                r = -r;
            }
        }
        if (g[i][i]) r *= g[i][i];
        else return 0;
    }
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> g[i][j];
        cout << determinant() << '\n';
    }
    cout << "*\n";

    return 0;
}
