// Candle Box
// UVa ID: 13161
// Verdict: Accepted
// Submission Date: 2022-10-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int sum[64] = {0};
    for (int i = 1; i <= 60; i++) sum[i] = sum[i - 1] + i;
    int D, R, T;
    while (cin >> D >> R >> T)
    {
        for (int i = 4; i <= 60; i++)
        {
            if (i < 3 + D) continue;
            int S = (sum[i] - 6) + (sum[i] - 3);
            for (int j = 1, k = i; j <= D; j++, k--) S -= k;
            if (S == R + T)
            {
                cout << R - (sum[i] - 6) << '\n';
                break;
            }
        }
    }

    return 0;
}
