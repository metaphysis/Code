// Contemplation! Algebra
// UVa ID: 10655
// Verdict: Accepted
// Submission Date: 2018-04-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// (a^n+b^n)(a+b)=a^(n+1)+b^(n+1)+ab(a^(n-1)+b^(n-1)) =>
// a^(n+1)+b^(n+1)=(a^n+b^n)(a+b)-ab(a^(n-1)+b^(n-1))
// F(n)=a^n+b^n => F(n)=p*F(n-1)-q*F(n-2), n>=2.

#include <bits/stdc++.h>

using namespace std;

struct matrix
{
    long long cell[2][2];
    matrix(long long a = 0, long long b = 0, long long c = 0, long long d = 0)
    {
        cell[0][0] = a, cell[0][1] = b, cell[1][0] = c, cell[1][1] = d;
    }
} one(1, 1, 1, 0);

matrix multiply(const matrix &a, const matrix &b)
{
    matrix r;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            r.cell[i][j] = a.cell[i][0] * b.cell[0][j] + a.cell[i][1] * b.cell[1][j];
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

    long long p, q, n;
    string line;

    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> p >> q;
        if (iss >> n)
        {
            if (n == 0) cout << 2 << '\n';
            else if (n == 1) cout << p << '\n';
            else
            {
                one = matrix(p, -q, 1, 0);
                matrix r = matrixPow(n - 1);
                long long v = r.cell[0][0] * p + r.cell[0][1] * 2;
                cout << v << '\n';
            }
        }
    }

    return 0;
}
