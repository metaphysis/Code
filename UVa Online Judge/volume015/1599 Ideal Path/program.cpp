// Ideal Path
// UVa ID: 1599
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.110s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100005;
const int INF = 1e9;

struct Edge {
    int to, color;
};

int n, m;
vector<Edge> graph[MAXN];
int dist[MAXN];
bool vis[MAXN];
vector<int> curLayer, nextLayer;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) {
            graph[i].clear();
        }

        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            graph[a].push_back({b, c});
            graph[b].push_back({a, c});
        }

        // 从终点 n 开始 BFS，计算每个节点到终点的最短距离
        fill(dist, dist + n + 1, INF);
        queue<int> q;
        dist[n] = 0;
        q.push(n);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (const Edge& e : graph[u]) {
                if (dist[e.to] > dist[u] + 1) {
                    dist[e.to] = dist[u] + 1;
                    q.push(e.to);
                }
            }
        }

        // 从起点 1 开始构造理想路径
        fill(vis, vis + n + 1, false);
        curLayer.clear();
        curLayer.push_back(1);
        vis[1] = true;

        vector<int> colors;  // 存储理想路径的颜色序列

        // 按层处理，共 dist[1] 层（从 1 到 n 的步数）
        for (int step = 0; step < dist[1]; step++) {
            // 找出从当前层所有节点出发，通往下一层的边的最小颜色
            int minColor = INF;
            for (int u : curLayer) {
                for (const Edge& e : graph[u]) {
                    // 只考虑在最短路径上的边
                    if (dist[e.to] == dist[u] - 1) {
                        minColor = min(minColor, e.color);
                    }
                }
            }

            colors.push_back(minColor);  // 记录当前层选择的最小颜色

            // 收集所有通过最小颜色边到达的下一层节点
            nextLayer.clear();
            for (int u : curLayer) {
                for (const Edge& e : graph[u]) {
                    if (dist[e.to] == dist[u] - 1 && e.color == minColor && !vis[e.to]) {
                        vis[e.to] = true;
                        nextLayer.push_back(e.to);
                    }
                }
            }

            // 更新当前层为下一层，继续处理
            curLayer.swap(nextLayer);
            // 去重，避免重复处理同一节点
            sort(curLayer.begin(), curLayer.end());
            curLayer.erase(unique(curLayer.begin(), curLayer.end()), curLayer.end());
        }

        // 输出结果
        cout << colors.size() << "\n";
        for (size_t i = 0; i < colors.size(); i++) {
            if (i > 0) cout << " ";
            cout << colors[i];
        }
        cout << "\n";
    }

    return 0;
}
