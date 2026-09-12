#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007;

vector<int> calcPoly(const vector<int>& vals) {
    int sum = 0;
    for (int v : vals) sum += v;
    vector<int> dp(sum + 1, 0);
    dp[0] = 1;
    int cur = 0;
    for (int a : vals) {
        if (a == 0) continue;
        vector<int> ndp(cur + a + 1, 0);
        for (int s = 0; s <= cur; ++s) if (dp[s]) {
            for (int x = 0; x <= a; ++x)
                ndp[s + x] = (ndp[s + x] + dp[s]) % MOD;
        }
        cur += a;
        dp.swap(ndp);
    }
    return dp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int R, C, L;
        cin >> R >> C >> L;
        vector<vector<int>> grid(R, vector<int>(C));
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j) cin >> grid[i][j];
        vector<vector<int>> compId(R, vector<int>(C, -1));
        int compCnt = 0;
        int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
        for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
            if (grid[i][j] == -1 || compId[i][j] != -1) continue;
            queue<pair<int,int>> q;
            q.push({i, j});
            compId[i][j] = compCnt;
            while (!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                    if (grid[nr][nc] == -1 || compId[nr][nc] != -1) continue;
                    compId[nr][nc] = compCnt;
                    q.push({nr, nc});
                }
            }
            compCnt++;
        }
        vector<vector<int>> blackVals(compCnt), whiteVals(compCnt);
        for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
            if (grid[i][j] == -1) continue;
            int id = compId[i][j];
            if ((i + j) & 1) whiteVals[id].push_back(grid[i][j]);
            else blackVals[id].push_back(grid[i][j]);
        }
        vector<int> dp(L + 1, 0);
        dp[0] = 1;
        for (int id = 0; id < compCnt; ++id) {
            vector<int> A = calcPoly(blackVals[id]);
            vector<int> B = calcPoly(whiteVals[id]);
            int sumB = 0, sumW = 0;
            for (int v : blackVals[id]) sumB += v;
            for (int v : whiteVals[id]) sumW += v;
            int D = sumB - sumW;
            vector<int> f(L + 1, 0);
            int maxS = min(sumB, L + D);
            for (int S = 0; S <= maxS; ++S) {
                if (A[S] == 0) continue;
                int whiteS = S - D;
                if (whiteS < 0 || whiteS > sumW) continue;
                if (B[whiteS] == 0) continue;
                int t = 2 * S - D;
                if (t < 0 || t > L) continue;
                f[t] = (f[t] + A[S] * B[whiteS]) % MOD;
            }
            vector<int> ndp(L + 1, 0);
            for (int s = 0; s <= L; ++s) if (dp[s]) {
                for (int t = 0; s + t <= L; ++t) if (f[t]) {
                    ndp[s + t] = (ndp[s + t] + dp[s] * f[t]) % MOD;
                }
            }
            dp.swap(ndp);
        }
        int ans = 0;
        for (int t = 0; t <= L; ++t) ans = (ans + dp[t]) % MOD;
        cout << ans << "\n";
    }
    return 0;
}
