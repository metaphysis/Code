// Siege
// UVa ID: 10607
// Verdict: Accepted
// Submission Date: 2026-05-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int M, N;
vector<string> grid;
int provId[205][205];
int provCount;
vector<pair<int,int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 四连通区域标记，给每个格子分配省份编号
void labelProvinces() {
    provCount = 0;
    memset(provId, -1, sizeof(provId));
    for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) {
        if (provId[i][j] != -1) continue;
        queue<pair<int,int>> q;
        q.push({i, j});
        provId[i][j] = provCount;
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < M && ny >= 0 && ny < N && provId[nx][ny] == -1 && grid[nx][ny] == grid[x][y]) {
                    provId[nx][ny] = provCount;
                    q.push({nx, ny});
                }
            }
        }
        ++provCount;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> M >> N, M || N) {
        grid.resize(M);
        for (int i = 0; i < M; ++i) cin >> grid[i];

        labelProvinces();

        // 找到首都的省份编号
        int capId = -1;
        for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j)
            if (grid[i][j] == 'A') capId = provId[i][j];

        // 建图：省份邻接表（使用 set 去重）
        vector<set<int>> adj(provCount);
        for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) {
            for (auto [dx, dy] : dirs) {
                int ni = i + dx, nj = j + dy;
                if (ni >= 0 && ni < M && nj >= 0 && nj < N) {
                    int u = provId[i][j], v = provId[ni][nj];
                    if (u != v) adj[u].insert(v);
                }
            }
        }

        // 标记边境省
        vector<bool> isBorder(provCount, false);
        for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j)
            if (i == 0 || i == M - 1 || j == 0 || j == N - 1)
                isBorder[provId[i][j]] = true;

        // BFS 从所有边境省出发（不经过首都），看能否到达所有非 A 省
        vector<bool> reachable(provCount, false);
        queue<int> q;
        for (int i = 0; i < provCount; ++i)
            if (isBorder[i] && i != capId) {
                reachable[i] = true;
                q.push(i);
            }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (v == capId) continue;
                if (!reachable[v]) {
                    reachable[v] = true;
                    q.push(v);
                }
            }
        }

        // 检查是否有非 A 省无法到达
        bool ok = true;
        for (int i = 0; i < provCount; ++i)
            if (i != capId && !reachable[i]) {
                ok = false;
                break;
            }
        if (!ok) {
            cout << "-1\n";
            continue;
        }

        // 找出与首都相邻的省份集合 S
        set<int> neighborSet;
        for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) {
            if (provId[i][j] != capId) continue;
            for (auto [dx, dy] : dirs) {
                int ni = i + dx, nj = j + dy;
                if (ni >= 0 && ni < M && nj >= 0 && nj < N) {
                    int nid = provId[ni][nj];
                    if (nid != capId) neighborSet.insert(nid);
                }
            }
        }

        // 如果 S 中有边境省，直接征服 S 即可
        bool hasBorderNeighbor = false;
        for (int x : neighborSet)
            if (isBorder[x]) {
                hasBorderNeighbor = true;
                break;
            }
        if (hasBorderNeighbor) {
            cout << neighborSet.size() << '\n';
            continue;
        }

        // 否则 BFS 计算从边境省到 S 的最短距离（路径上的省份数，起点距离为 1）
        vector<int> dist(provCount, -1);
        queue<int> bq;
        for (int i = 0; i < provCount; ++i)
            if (isBorder[i] && i != capId) {
                dist[i] = 1;
                bq.push(i);
            }
        while (!bq.empty()) {
            int u = bq.front(); bq.pop();
            for (int v : adj[u]) {
                if (v == capId) continue;
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    bq.push(v);
                }
            }
        }

        int minDist = 1e9;
        for (int x : neighborSet)
            if (dist[x] != -1)
                minDist = min(minDist, dist[x]);

        cout << neighborSet.size() + minDist - 1 << '\n';
    }

    return 0;
}
