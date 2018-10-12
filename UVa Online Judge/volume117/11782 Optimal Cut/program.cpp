// Optimal Cut
// UVa ID: 11782
// Verdict: Accepted
// Submission Date: 2018-10-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;

int H, K, Wi[1 << 20], dp[1 << 20][21];

void read(int idx, int h)
{
    cin >> Wi[idx];
    if (h)
    {
        read(2 * idx + 1, h - 1);
        read(2 * idx + 2, h - 1);
    }
}

int dfs(int idx, int h, int k)
{
    if (h == H) return Wi[idx];
    if (dp[idx][k] != -INF) return dp[idx][k];
    int r = Wi[idx];
    for (int i = 1; i < k; i++)
    {
        int next = dfs(2 * idx + 1, h + 1, i) + dfs(2 * idx + 2, h + 1, k - i);
        r = max(r, next);
    }
    return dp[idx][k] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> H)
    {
        if (H == -1) break;
        cin >> K;
        read(0, H);
        for (int i = 0; i < (1 << H); i++)
            for (int j = 0; j <= K; j++)
                dp[i][j] = -INF;
        cout << dfs(0, 0, K) << '\n';
    }

    return 0;
}
