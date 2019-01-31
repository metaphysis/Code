// Income Tax Hazard (II)
// UVa ID: 11667
// Verdict: Accepted
// Submission Date: 2019-01-31
// UVa Run Time: 0.710s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    double M, S1, S2;
    while (cin >> M >> S1 >> S2)
    {
        if (M == 0) break;
        double P = 0;
        for (int i = S1; i <= S2; i++) P += (S2 - i + 1);
        double T = 0;
        if (M > S1)
        {
            if (M < S2)
            {
                for (int i = S1; i <= M; i++)
                    T += (M - i) * (M - i + 1) * 0.15 + (S2 - M) * (M - i) * 0.1;
            }
            else
            {
                for (int i = S1; i <= S2; i++)
                    T += (S2 - i) * (S2 - i + 1) * 0.05 + (2 * M - i - S2) * (S2 - i + 1) * 0.1;
            }
        }
        cout << "Case " << ++cases << ": ";
        cout << fixed << setprecision(2) << (T / P) << '\n';
    }

    return 0;
}
