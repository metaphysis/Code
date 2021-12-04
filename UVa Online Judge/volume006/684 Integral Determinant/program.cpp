// Integral Determinant
// UVa ID: 684
// Verdict: Accepted
// Submission Date: 2021-12-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
long long g[32][32];

long long determinant()
{
    long long r = 1;
    for (int i = 0; i < n - 1; i++)
    {
        int operated = 0;
        do
        {
            int z = -1;
            for (int j = i; j < n; j++)
            {
                if (g[j][i] < 0)
                {
                    for (int k = i; k < n; k++) g[j][k] *= -1;
                    r *= -1;
                }
                if (g[j][i] == 1) { z = j; break; }
                if (g[j][i] && (z == -1 || g[j][i] < g[z][i])) z = j;
            }
            if (z == -1) return 0;
            if (z != i)
            {
                swap(g[i], g[z]);
                r *= -1;
            }
            operated = 0;
            for (int j = i + 1; j < n; j++)
                if (g[j][i])
                {
                    operated = 1;
                    long long c = g[j][i] / g[i][i];
                    for (int k = i; k < n; k++) g[j][k] -= c * g[i][k];
                }
        } while (operated && g[i][i] != 1);
    }
    for (int i = 0; i < n; i++) r *= g[i][i];
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
