// Probability|Given
// UVa ID: 11181
// Verdict: Accepted
// Submission Date: 2018-06-05
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, r, cases = 0;
    double pi[24], pc[24], pa, pt;

    while (cin >> N >> r)
    {
        if (N == 0) break;

        for (int i = 0; i < N; i++)
        {
            cin >> pi[i];
            pc[i] = 0.0;
        }

        pt = 0.0;
        for (int i = 0; i < (1 << N); i++)
        {
            if (__builtin_popcount(i) == r)
            {
                pa = 1.0;
                for (int j = 0, k = i; j < N; j++, k >>= 1)
                {
                    if (k & 1) pa *= pi[j];
                    else pa *= (1.0 - pi[j]);
                }
                pt += pa;
                for (int j = 0, k = i; j < N; j++, k >>= 1)
                    if (k & 1) pc[j] += pa;
            }
        }

        cout << "Case " << ++cases << ":\n";
        for (int i = 0; i < N; i++)
        {
            cout << fixed << setprecision(6) << pc[i] / pt << '\n';
        }
    }

    return 0;
}
