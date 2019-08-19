// Knight Tour
// UVa ID: 11643
// Verdict: Accepted
// Submission Date: 2019-08-19
// UVa Run Time: 0.380s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f, THRESHOLD = 20;

int N, K, D1[1010][1010], D2[1010][1010], visited[1010][1010] = {}, g[16][16], kr[16], kc[16];
int dp[16][1 << 16];
int dr[8] = {2, 2, 1, 1, -2, -2, -1, -1};
int dc[8] = {1, -1, 2, -2, 1, -1, 2, -2};

bool inBounds(int r, int c, int n)
{
    return r >= 0 && r < n && c >= 0 && c < n;
}

void bfs1()
{
    memset(D1, INF, sizeof(D1));
    queue<int> R, C;
    R.push(0); C.push(0);
    D1[0][0] = 0;
    int r, c, nr, nc;
    while (!R.empty())
    {
        r = R.front(); R.pop();
        c = C.front(); C.pop();
        for (int k = 0; k < 8; k++)
        {
            int nr = r + dr[k], nc = c + dc[k];
            if (inBounds(nr, nc, 1000) && D1[nr][nc] > D1[r][c] + 1)
            {
                D1[nr][nc] = D1[r][c] + 1;
                R.push(nr); C.push(nc);
            }
        }
    }
}

int bfs2(int r1, int c1, int r2, int c2)
{
    static int tag = 0;
    tag++;
    queue<int> R, C;
    R.push(r1); C.push(c1);
    D2[r1][c1] = 0;
    visited[r1][c1] = tag;
    while (!R.empty())
    {
        r1 = R.front(); R.pop();
        c1 = C.front(); C.pop();
        // 对于较远的位置不求最短距离。
        if (D2[r1][c1] > THRESHOLD + 10) break;
        for (int k = 0; k < 8; k++)
        {
            int nr = r1 + dr[k], nc = c1 + dc[k];
            if (inBounds(nr, nc, N) && visited[nr][nc] != tag)
            {
                // 为已访问位置赋予标记以避免反复初始化距离数组。
                visited[nr][nc] = tag;
                D2[nr][nc] = D2[r1][c1] + 1;
                // 及早返回结果。
                if (nr == r2 && nc == c2) return D2[nr][nc];
                R.push(nr); C.push(nc);
            }
        }
    }
    return D2[r2][c2];
}

int dfs(int u, int mask)
{
    if (mask == (1 << K) - 1) return g[u][0];
    if (~dp[u][mask]) return dp[u][mask];
    int r = INF;
    for (int v = 0; v < K; v++)
        if (v != u && !(mask & (1 << v)))
            r = min(r, g[u][v] + dfs(v, mask | (1 << v)));
    return dp[u][mask] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    bfs1();

    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N >> K;
        for (int i = 0; i < K; i++)
        {
            cin >> kr[i] >> kc[i];
            kr[i]--, kc[i]--;
        }
        for (int i = 0; i < K; i++)
            for (int j = 0; j < K; j++)
                // 当横纵坐标差值大于阈值时使用预先计算的最短距离。
                if (abs(kr[i] - kr[j]) + abs(kc[i] - kc[j]) > THRESHOLD)
                    g[i][j] = D1[abs(kr[i] - kr[j])][abs(kc[i] - kc[j])];
                else
                    // 实时计算最短距离。
                    g[i][j] = bfs2(kr[i], kc[i], kr[j], kc[j]);
        cout << "Case " << cs << ": ";
        memset(dp, -1, sizeof(dp));
        cout << dfs(0, 1) << '\n';
    }

    return 0;
}
