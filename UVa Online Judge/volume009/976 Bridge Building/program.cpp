// Bridge Building
// UVa ID: 976
// Verdict: Accepted
// Submission Date: 2018-10-15
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int R, C, B, S;
char grid[1001][1001];
int dp[1001][101], lower[1001], higher[1001], height[1001];

void getHigher(int i, int j)
{
    if (grid[i][j] == '#')
    {
        higher[j] = max(higher[j], i);
        grid[i][j] = '.';
        if (i + 1 < R) getHigher(i + 1, j);
        if (i) getHigher(i - 1, j);
        if (j + 1 < C) getHigher(i, j + 1);
        if (j) getHigher(i, j - 1);
    }
}

void getLower(int i, int j)
{
    if (grid[i][j] == '#')
    {
        lower[j] = min(lower[j], i);
        grid[i][j] = '.';
        if (i + 1 < R) getLower(i + 1, j);
        if (i) getLower(i - 1, j);
        if (j + 1 < C) getLower(i, j + 1);
        if (j) getLower(i, j - 1);
    }
}

int dfs(int idx, int bridge)
{
    if (bridge == B) return 0;
    if (idx + (B - bridge - 1) * (S + 1) >= C) return INF;
    if (~dp[idx][bridge]) return dp[idx][bridge];
    int r = dfs(idx + 1, bridge);
    r = min(r, height[idx] + dfs(idx + S + 1, bridge + 1));
    return dp[idx][bridge] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> R >> C)
    {
        cin >> B >> S;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                cin >> grid[i][j];

        memset(higher, 0, sizeof(higher));
        getHigher(0, 0);

        memset(lower, 0x3f, sizeof(lower));
        getLower(R - 1, 0);

        for (int i = 0; i < C; i++) height[i] = lower[i] - higher[i] - 1;
            
        memset(dp, -1, sizeof(dp));
        cout << dfs(0, 0) << '\n';
    }

    return 0;
}
