// Tribonacci
// UVa ID: 12470
// Verdict: Accepted
// Submission Date: 2018-04-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3;

long long d, n, m = 1000000009LL, a[MAXN], f[MAXN];

struct matrix
{
    long long cell[MAXN][MAXN] = {};
    matrix() {}
    matrix(long long c[])
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

    d = 3;
    a[0] = a[1] = a[2] = 1;
    f[0] = 2, f[1] = 1, f[2] = 0;
    
    while (cin >> n, n > 0)
    {
        if (n <= d) cout << f[d - n] % m << '\n';
        else
        {
            one = matrix(a);
            matrix r = matrixPow(n - 3);
            long long tn = 0;
            for (int i = 0; i < d; i++)
                tn += (r.cell[0][i] * f[i]) % m;
            cout << tn % m << '\n';
        }
        
    }

    return 0;
}
