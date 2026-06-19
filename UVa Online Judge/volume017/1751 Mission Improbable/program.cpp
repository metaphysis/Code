// Mission Improbable
// UVa ID: 1751
// Verdict: Accepted
// Submission Date: 2026-06-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1LL << 60;

// KM算法求最大权完美匹配 (n <= 100)
ll kmMaxWeight(const vector<vector<ll>>& w) {
    int n = (int)w.size();
    vector<ll> lx(n, 0), ly(n, 0), slack(n);
    vector<int> matchY(n, -1), matchX(n, -1);
    vector<bool> visX(n), visY(n);

    // 初始化顶标 lx：每行最大值
    for (int i = 0; i < n; ++i) {
        lx[i] = *max_element(w[i].begin(), w[i].end());
    }

    // DFS 找增广路
    function<bool(int)> dfs = [&](int x) {
        visX[x] = true;
        for (int y = 0; y < n; ++y) {
            if (!visY[y]) {
                ll gap = lx[x] + ly[y] - w[x][y];
                if (gap == 0) {
                    visY[y] = true;
                    if (matchY[y] == -1 || dfs(matchY[y])) {
                        matchY[y] = x;
                        matchX[x] = y;
                        return true;
                    }
                } else {
                    slack[y] = min(slack[y], gap);
                }
            }
        }
        return false;
    };

    // 对每一行进行匹配
    for (int i = 0; i < n; ++i) {
        fill(slack.begin(), slack.end(), INF);
        while (true) {
            fill(visX.begin(), visX.end(), false);
            fill(visY.begin(), visY.end(), false);
            if (dfs(i)) break;
            ll d = INF;
            for (int j = 0; j < n; ++j)
                if (!visY[j]) d = min(d, slack[j]);
            for (int j = 0; j < n; ++j) {
                if (visX[j]) lx[j] -= d;
                if (visY[j]) ly[j] += d;
                else slack[j] -= d;
            }
        }
    }

    ll total = 0;
    for (int i = 0; i < n; ++i)
        if (matchX[i] != -1) total += w[i][matchX[i]];
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c;
    while (cin >> r >> c) {
        vector<vector<ll>> h(r, vector<ll>(c));
        ll total = 0;
        int base = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> h[i][j];
                total += h[i][j];
                if (h[i][j] > 0) ++base;
            }
        }

        vector<ll> rowMax(r, 0), colMax(c, 0);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j) {
                rowMax[i] = max(rowMax[i], h[i][j]);
                colMax[j] = max(colMax[j], h[i][j]);
            }

        ll rowSum = 0, colSum = 0;
        for (int i = 0; i < r; ++i)
            if (rowMax[i] > 1) rowSum += rowMax[i] - 1;
        for (int j = 0; j < c; ++j)
            if (colMax[j] > 1) colSum += colMax[j] - 1;

        // 构建二分图权值矩阵，行列数扩充至 n = max(r,c)
        int n = max(r, c);
        vector<vector<ll>> weight(n, vector<ll>(n, 0));
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                if (rowMax[i] == colMax[j] && rowMax[i] > 1 && h[i][j] > 0)
                    weight[i][j] = rowMax[i] - 1;

        ll maxMatch = kmMaxWeight(weight);

        ll minRemain = (ll)base + rowSum + colSum - maxMatch;
        ll ans = total - minRemain;
        cout << ans << '\n';
    }
    return 0;
}
