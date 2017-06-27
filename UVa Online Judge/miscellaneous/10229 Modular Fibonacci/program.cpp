// Modular Fibonacci
// UVa ID: 10229
// Verdict: Accepted
// Submission Date: 2017-06-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

long long n, m, fmodm;

struct matrix
{
    long long element[2][2];
    matrix(long long a = 0, long long b = 0, long long c = 0, long long d = 0)
    {
        element[0][0] = a, element[0][1] = b, element[1][0] = c, element[1][1] = d;
    }
};

matrix zero(1, 0, 0, 1), one(1, 1, 1, 0);

matrix multiply(const matrix & a, const matrix & b)
{
    matrix r;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            r.element[i][j] = (a.element[i][0] * b.element[0][j] + a.element[i][1] * b.element[1][j]) % m;
    return r;
}

matrix pow_matrix(long long k)
{
    if (k == 0) return zero;
    if (k == 1) return one;

    matrix r = pow_matrix(k / 2);
    r = multiply(r, r);
    if (k % 2) r = multiply(r, one);

    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        if (n == 0 || m == 0) fmodm = 0;
        else
        {
            m = 1 << m;
            matrix r = pow_matrix(n - 1);
            fmodm = r.element[0][0];
        }

        cout << fmodm << '\n';
    }

    return 0;
}
