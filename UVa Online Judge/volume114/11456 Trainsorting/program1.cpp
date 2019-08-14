// Trainsorting
// UVa ID: 11456
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2010;

int n, weight[MAXN], dp1[MAXN][MAXN], dp2[MAXN][MAXN];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    while (cases--)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> weight[i];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dp1[i][j] = dp2[i][j] = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                if (weight[i] > weight[j])
                    dp1[i][i] = max(dp1[i][i], dp1[i - 1][j] + 1);
                else
                    dp2[i][i] = max(dp2[i][i], dp2[i - 1][j] + 1);
            }
        int r = 0;
        for (int i = 0; i < n; i++)
            r = max(r, dp1[i][i] + dp2[i][i] - 1);
        cout << r << '\n';
    }

    return 0;
}
