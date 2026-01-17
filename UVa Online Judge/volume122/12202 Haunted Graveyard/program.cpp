// Haunted Graveyard
// UVa ID: 12202
// Verdict: Accepted
// Submission Date: 2026-01-10
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to, cost;
};

const int INF = 1e9;
const int MAX_N = 905; // 最大节点数：30*30=900

int W, H, G, E;
int gravestone[32][32]; // 标记墓碑
int hole[32][32][3];    // hole[x][y][0/1/2] -> 目标x, 目标y, 时间差
int dist[MAX_N];
vector<Edge> edges;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> W >> H, W || H) {
        memset(gravestone, 0, sizeof gravestone);
        memset(hole, -1, sizeof hole); // -1 表示没有鬼洞
        edges.clear();

        // 读入墓碑
        cin >> G;
        for (int i = 0; i < G; ++i) {
            int x, y;
            cin >> x >> y;
            gravestone[x][y] = 1;
        }

        // 读入鬼洞
        cin >> E;
        for (int i = 0; i < E; ++i) {
            int x1, y1, x2, y2, t;
            cin >> x1 >> y1 >> x2 >> y2 >> t;
            hole[x1][y1][0] = x2;
            hole[x1][y1][1] = y2;
            hole[x1][y1][2] = t;
        }

        // 建图
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (int x = 0; x < W; ++x) {
            for (int y = 0; y < H; ++y) {
                int u = y * W + x;
                // 如果是终点或墓碑，不添加普通移动边
                if (x == W - 1 && y == H - 1) continue;
                if (gravestone[x][y]) continue;

                // 如果该格有鬼洞，只添加鬼洞边
                if (hole[x][y][0] != -1) {
                    int x2 = hole[x][y][0], y2 = hole[x][y][1], t = hole[x][y][2];
                    int v = y2 * W + x2;
                    edges.push_back({u, v, t});
                } else {
                    // 否则添加普通移动边
                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dirs[d][0], ny = y + dirs[d][1];
                        if (nx >= 0 && nx < W && ny >= 0 && ny < H && !gravestone[nx][ny]) {
                            int v = ny * W + nx;
                            edges.push_back({u, v, 1});
                        }
                    }
                }
            }
        }

        // Bellman-Ford
        int V = W * H;
        fill(dist, dist + V, INF);
        dist[0] = 0;

        // 执行 V-1 次松弛
        for (int i = 0; i < V - 1; ++i) {
            bool updated = false;
            for (const Edge& e : edges) {
                if (dist[e.from] < INF && dist[e.to] > dist[e.from] + e.cost) {
                    dist[e.to] = dist[e.from] + e.cost;
                    updated = true;
                }
            }
            if (!updated) break;
        }

        // 检查是否存在从起点可达的负环
        bool hasNegativeCycle = false;
        for (const Edge& e : edges) {
            if (dist[e.from] < INF && dist[e.to] > dist[e.from] + e.cost) {
                // 存在负环，并且从起点可达
                hasNegativeCycle = true;
                break;
            }
        }

        // 输出结果
        if (hasNegativeCycle) {
            cout << "Never\n";
        } else if (dist[V - 1] == INF) {
            cout << "Impossible\n";
        } else {
            cout << dist[V - 1] << "\n";
        }
    }

    return 0;
}
