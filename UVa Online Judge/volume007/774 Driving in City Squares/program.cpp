// Driving in City Squares
// UVa ID: 774
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n) {
        cin >> m;
        int h, v;
        cin >> h >> v;
        vector<int> s(h - 1), a(v - 1);
        for (int i = 0; i < h - 1; ++i) cin >> s[i];
        for (int i = 0; i < v - 1; ++i) cin >> a[i];
        vector<vector<int>> fee(h, vector<int>(v));
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < v; ++j)
                cin >> fee[i][j];
        int w1, t1, w2, t2;
        cin >> w1 >> t1 >> w2 >> t2;
        // 计算每个县的边界
        vector<int> north(h), south(h), west(v), east(v);
        for (int i = 0; i < h; ++i) {
            north[i] = (i == 0) ? 0 : s[i - 1];
            south[i] = (i == h - 1) ? n : s[i];
        }
        for (int j = 0; j < v; ++j) {
            west[j] = (j == 0) ? 0 : a[j - 1];
            east[j] = (j == v - 1) ? m : a[j];
        }
        // 确定起始县集合和目标县集合
        vector<int> startNodes, targetNodes;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < v; ++j) {
                int id = i * v + j;
                if (w1 >= north[i] && w1 <= south[i] && t1 >= west[j] && t1 <= east[j])
                    startNodes.push_back(id);
                if (w2 >= north[i] && w2 <= south[i] && t2 >= west[j] && t2 <= east[j])
                    targetNodes.push_back(id);
            }
        }
        int N = h * v;
        int S = N;                        // 超级源点
        vector<vector<pair<int, int>>> adj(N + 1);
        // 超级源点到所有起始节点距离0
        for (int id : startNodes) adj[S].push_back({id, 0});
        // 相邻县之间的边，边权为目标县费用
        int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < v; ++j) {
                int u = i * v + j;
                for (auto &d : dirs) {
                    int ni = i + d[0], nj = j + d[1];
                    if (ni < 0 || ni >= h || nj < 0 || nj >= v) continue;
                    int vNode = ni * v + nj;
                    adj[u].push_back({vNode, fee[ni][nj]});
                }
            }
        }
        // Dijkstra
        vector<int> dist(N + 1, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[S] = 0;
        pq.push({0, S});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (auto &[vNode, w] : adj[u]) {
                if (dist[vNode] > dist[u] + w) {
                    dist[vNode] = dist[u] + w;
                    pq.push({dist[vNode], vNode});
                }
            }
        }
        int ans = INF;
        for (int id : targetNodes) ans = min(ans, dist[id]);
        cout << ans << '\n';
        // 读取实例结束标记 '%'
        string endMark;
        cin >> endMark;   // 应为 "%"
    }
    return 0;
}
