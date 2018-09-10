// KTV
// UVa ID: 11218
// Verdict: Accepted
// Submission Date: 2018-09-11
// UVa Run Time: 0.180s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n;
    int a, b, c, s;

    while (cin >> n, n > 0)
    {
        int score[100][2] = {};
        for (int i = 0; i < n; i++)
        {
            cin >> a >> b >> c >> s;
            a--, b--, c--;
            score[i][0] = ((1 << a) | (1 << b) | (1 << c));
            score[i][1] = s;
        }
        int maxValue = -1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                {
                    if (i == j || j == k || i == k) continue;
                    if ((score[i][0] | score[j][0] | score[k][0]) != 0x1ff) continue;
                    maxValue = max(maxValue, score[i][1] + score[j][1] + score[k][1]);
                }

        cout << "Case " << ++cases << ": " << maxValue << '\n';
    }

    return 0;
}
