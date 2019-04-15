// Ultimate Mango Challenge
// UVa ID: 12996
// Verdict: Accepted
// Submission Date: 2019-04-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N, L, A[16], B[16], S;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> L;
        S = 0;
        for (int i = 0; i < N; i++) { cin >> A[i]; S += A[i]; }
        for (int i = 0; i < N; i++) cin >> B[i];
        bool yes = (S <= L);
        if (yes)
        {
            for (int i = 0; i < N; i++)
                if (A[i] > B[i])
                {
                    yes = false;
                    break;
                }
        }
        cout << "Case " << t << ": " << (yes ? "Yes" : "No") << '\n';
    }

    return 0;
}
