// The Miser's Puzzle
// UVa ID: 12852
// Verdict: Accepted
// Submission Date: 2022-10-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T; cin >> T;
    for (int cases = 1; cases <= T; cases++)
    {
        int N; cin >> N;
        long long LCM = 1, Mi;
        while (N--)
        {
            cin >> Mi;
            LCM = LCM * Mi / __gcd(LCM, Mi);
        }
        cout << "Case " << cases << ": " << LCM * 35 << '\n';
    }

    return 0;
}
