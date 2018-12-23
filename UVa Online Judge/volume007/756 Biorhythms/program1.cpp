// Biorhythms
// UVa ID: 756
// Verdict: Accepted
// Submission Date: 2018-12-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void extgcd(int a, int b, int &x, int &y)
{
    if (b == 0) x = 1, y = 0;
    else
    {
        extgcd(b, a % b, x, y);
        int t = x - a / b * y;
        x = y, y = t;
    }
}

int CRT(int a[], int m[], int n, int d)
{
    int M = 1, r = 0;
    for (int i = 0; i < n; i++) M *= m[i];
    for (int i = 0, Mi, x, y; i < n; i++)
    {
        Mi = M / m[i];
        extgcd(Mi, m[i], x, y);
        r = (r + a[i] * Mi * x) % M;
    }
    if (r <= d) r += ((d - r) / M + 1) * M;
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int p, e, i, d, cases = 0;
    while (cin >> p >> e >> i >> d)
    {
        if (p == -1) break;
        int a[] = {p, e, i};
        int m[] = {23, 28, 33};
        int r = CRT(a, m, 3, d);
        cout << "Case " << ++cases << ": the next triple peak occurs in ";
        cout << (r - d) << " days.\n";
    }

    return 0;
}
