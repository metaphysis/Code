// Candy
// UVa ID: 1639
// Verdict: Accepted
// Submission Date: 2017-09-03
// UVa Run Time: 0.230s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const long double epsilon = 1e-7;
const int MAXN = 200005;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long double logn[2 * MAXN] = {0.0};
    for (int i = 1; i <= MAXN; i++) logn[i] = log(i) + logn[i - 1];

    int cases = 0, n;
    long double p;

    while (cin >> n >> p)
    {
        cout << "Case " << ++cases << ": ";

        if (fabs(p) < epsilon || fabs(p - 1.0) < epsilon)
        {
            cout << fixed << setprecision(6) << double(n) << '\n';
            continue;
        }

        long double expected = 0.0, logp = log(p), log1_p = log(1.0 - p);
        for (int i = 1; i <= n; i++)
        {
            long double c = logn[2 * n - i] - logn[n - i] - logn[n];
            long double e1 = c + (n + 1) * logp + (n - i) * log1_p;
            long double e2 = c + (n + 1) * log1_p + (n - i) * logp;
            expected += (exp(e1) + exp(e2)) * i;
        }

        cout << fixed << setprecision(6) << expected << '\n';
    }
    
    return 0;
}
