// Earn For Future
// UVa ID: 12614
// Verdict: Accepted
// Submission Date: 2019-02-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        int N, Ci, M = 0;
        cin >> N;
        for (int i = 1; i <= N; i++)
        {
            cin >> Ci;
            M = max(M, Ci);
        }
        cout << "Case " << t << ": " << M << '\n';
    }

    return 0;
}
