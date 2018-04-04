// Recurrences
// UVa ID: 10870
// Verdict: Accepted
// Submission Date: 2018-04-04
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 16;

long long d, n, m, a[MAXN], f[MAXN];

struct matrix
{
    long long cell[MAXN][MAXN] = {};
    matrix() {}
    matrix(long long c[], int d)
    {
        for (int i = 0; i < d; i++)
            cell[0][i] = c[i];
        for (int i = 1; i < d; i++)
            cell[i][i - 1] = 1;
    }
} one;

matrix multiply(const matrix &a, const matrix &b)
{
    matrix r;
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
        {
            r.cell[i][j] = 0;
            for (int k = 0; k < d; k++)
                r.cell[i][j] += (a.cell[i][k] * b.cell[k][j]) % m;
            r.cell[i][j] %= m;
        }
    return r;
}

matrix matrixPow(long long k)
{
    if (k == 1) return one;
    matrix r = matrixPow(k >> 1);
    r = multiply(r, r);
    if (k & 1) r = multiply(r, one);
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> d >> n >> m)
    {
        if (d == 0) break;
        for (int i = 0; i < d; i++)
        {
            cin >> a[i];
            a[i] %= m;
        }
        
        for (int i = d - 1; i >= 0; i--)
        {
            cin >> f[i];
            f[i] %= m;
        }

        if (n <= d)
        {
            cout << f[n - 1] % m << '\n';
        }
        else
        {
            one = matrix(a, d);
            matrix r = matrixPow(n - d);
            long long fn = 0;
            for (int i = 0; i < d; i++)
                fn += (r.cell[0][i] * f[i]) % m;
            cout << fn % m << '\n';
        }
    }

    return 0;
}
