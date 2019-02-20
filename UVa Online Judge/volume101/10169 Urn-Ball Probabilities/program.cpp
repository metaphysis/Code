// Urn-Ball Probabilities
// UVa ID: 10169
// Verdict: Accepted
// Submission Date: 2019-02-20
// UVa Run Time: 0.020s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

double p[MAXN] = {1}, q[MAXN] = {0};
    
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, lastN = 0;

    while (cin >> n)
    {
        for (int i = lastN + 1; i <= n; i++)
        {
            p[i] = p[i - 1] * (1 - 1.0 / (1.0 * i * (i + 1)));
            q[i] = q[i - 1] + log10(1.0 * i * (i + 1));
        }
        cout << fixed << setprecision(6) << (1 - p[n]) << ' ' << (int)q[n] << '\n';
        lastN = max(lastN, n);
    }

    return 0;
}
