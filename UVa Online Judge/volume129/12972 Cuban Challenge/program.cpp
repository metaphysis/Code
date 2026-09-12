#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> dis, ml, mr;
    HopcroftKarp(int n, int m) : n(n), m(m), adj(n), dis(n), ml(n, -1), mr(m, -1) {}
    bool bfs() {
        queue<int> que;
        bool ok = false;
        for (int i = 0; i < n; i++) {
            if (ml[i] == -1) {
                dis[i] = 0;
                que.push(i);
            } else {
                dis[i] = -1;
            }
        }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v : adj[u]) {
                int w = mr[v];
                if (w == -1) {
                    ok = true;
                } else if (dis[w] == -1) {
                    dis[w] = dis[u] + 1;
                    que.push(w);
                }
            }
        }
        return ok;
    }
    bool dfs(int u) {
        for (int v : adj[u]) {
            int w = mr[v];
            if (w == -1 || (dis[w] == dis[u] + 1 && dfs(w))) {
                ml[u] = v;
                mr[v] = u;
                return true;
            }
        }
        dis[u] = -1;
        return false;
    }
    int solve() {
        int res = 0;
        while (bfs())
            for (int i = 0; i < n; i++)
                if (ml[i] == -1 && dfs(i)) res++;
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, tc = 0;
    while (cin >> n >> m && n) {
        vector<string> board(n);
        for (int i = 0; i < n; i++) cin >> board[i];
        vector<vector<int>> id(n, vector<int>(m, -1));
        int leftCnt = 0, rightCnt = 0, cellCnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (board[i][j] == '.') {
                    cellCnt++;
                    if ((i + j) % 2 == 0) id[i][j] = leftCnt++;
                    else id[i][j] = rightCnt++;
                }
        HopcroftKarp hk(leftCnt, rightCnt);
        int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (board[i][j] == '.' && (i + j) % 2 == 0)
                    for (int k = 0; k < 4; k++) {
                        int x = i + dx[k], y = j + dy[k];
                        if (x >= 0 && x < n && y >= 0 && y < m && board[x][y] == '.')
                            hk.adj[id[i][j]].push_back(id[x][y]);
                    }
        int matchCnt = hk.solve();
        int rest = cellCnt - 2 * matchCnt;
        cout << "Case #" << ++tc << ": " << (rest + 1) / 2 << '\n';
    }
    return 0;
}
