// Fishing
// UVa ID: 12870
// Verdict: Accepted
// Submission Date: 2023-06-22
// UVa Run Time: 0.590s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define BEST(T, A, B) (T ? max(A, B) : min(A, B))
#define FISH 1
#define NOURISH 0

const int MAXN = 110, INF = 0x3f3f3f3f;
int R, C, D[MAXN][MAXN];
int dp[2][MAXN][MAXN][MAXN], visited[2][MAXN][MAXN][MAXN];
int flag;

int dfs(int fn, int i, int j, int k) {
    if (k == 0) return 0;
    if (i <= 0 || j <= 0) return fn ? -INF : INF;
    if (visited[fn][i][j][k] == flag) return dp[fn][i][j][k];
    visited[fn][i][j][k] = flag;
    int r = dfs(fn, i - 1, j - 1, k - 1) + D[i][j];
    r = BEST(fn, r, dfs(fn, i - 1, j, k));
    r = BEST(fn, r, dfs(fn, i, j - 1, k));
    dfs(fn, i, j, k - 1);
    return dp[fn][i][j][k] = r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> R >> C;
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                cin >> D[i][j];
        int top = min(R, C) / 2;
        flag = T + 1;
        dfs(FISH, R, C, top);
        dfs(NOURISH, R, C, top * 2);
        int r = 0;
        for (int k = 0; k <= top; k++)
            r = max(r, dp[FISH][R][C][k] - dp[NOURISH][R][C][k * 2]);
        cout << r << '\n';
    }
    return 0;
}
