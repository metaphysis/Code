// How Many
// UVa ID: 986
// Verdict: Accepted
// Submission Date: 2019-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int LEFT_UP = 0, LEFT_DOWN = 1;

int dp[64][64][64][2], N, R, K;

int dfs(int x, int y, int r, int from)
{
    if (r > x / 2) return 0;
    if (y >= 2 * N || y < 0) return 0;
    if (x == 0) return y == 0 && r == 0 && from == LEFT_UP;
    if (~dp[x][y][r][from]) return dp[x][y][r][from];
    int ret = 0;
    if (from == LEFT_UP)
    {
        if (y + 1 == K) ret += dfs(x - 1, y + 1, r - 1, LEFT_DOWN);
        else ret += dfs(x - 1, y + 1, r, LEFT_DOWN);
        ret += dfs(x - 1, y + 1, r, LEFT_UP);
    }
    else
    {
        ret += dfs(x - 1, y - 1, r, LEFT_DOWN);
        ret += dfs(x - 1, y - 1, r, LEFT_UP);
    }
    return dp[x][y][r][from] = ret;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> R >> K)
    {
        memset(dp, -1, sizeof(dp));
        cout << dfs(2 * N, 0, R, LEFT_UP) << '\n';
    }

    return 0;
}
