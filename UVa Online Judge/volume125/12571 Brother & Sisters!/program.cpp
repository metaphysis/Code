// Brother & Sisters!
// UVa ID: 12571
// Verdict: Accepted
// Submission Date: 2022-01-04
// UVa Run Time: 0.110s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N, Q;
    int xi, ai[240], a;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N >> Q;
        memset(ai, 0, sizeof ai);
        for (int i = 1; i <= N; i++)
        {
            cin >> xi;
            for (int j = 0; j <= 230; j++)
                if ((xi & j) > ai[j])
                    ai[j] = (xi & j);
        }
        for (int i = 1; i <= Q; i++)
        {
            cin >> a;
            cout << ai[a] << '\n';
        }
    }
    return 0;
}
