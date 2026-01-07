// Knight on the Bee Board
// UVa ID: 10595
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20010, INF = 0x3f3f3f3f;

// 双向映射：编号<->坐标
map<int, pair<int, int>> idToPoint;
map<pair<int, int>, int> pointToId;

// 建立坐标和编号之间的双向映射
void initialize() {
    // 五个方向的偏移量，用于生成螺旋网格
    int offset[5][2] = {{-1, 0}, {0, -1}, {1, -1}, {1, 0}, {0, 1}};
    // i: 当前圈的起始编号, j: 当前圈的格子数, k: 当前圈数
    for (int i = 1, j = 1, k = 0; i < MAXN; i += j, j += 6, k++) {
        // 设置当前圈起始点的坐标
        idToPoint[i] = {0, k};
        pointToId[{0, k}] = i;
        // 填充起始点所在的对角线
        for (int m = 0; m < k; m++) {
            idToPoint[i - m] = {m, k - m};
            pointToId[{m, k - m}] = i - m;
        }
        int current = i;
        // 填充当前圈的其余部分（5条边）
        for (int m = 0; m < 5; m++)
            for (int n = 0; n < k; n++) {
                int x = idToPoint[current].first + offset[m][0];
                int y = idToPoint[current].second + offset[m][1];
                idToPoint[current + 1] = {x, y};
                pointToId[{x, y}] = current + 1;
                current++;
            }
    }
}

// 获取骑士从编号id可以跳到的所有格子（不超过N）
vector<int> getKnightMoves(int id, int N) {
    vector<int> moves;
    if (id < 1 || id > N) return moves;
    pair<int, int> p = idToPoint[id];
    // 六个方向的坐标偏移
    int offset[6][2] = {{0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}, {1, 0}};
    for (int i = 0; i < 6; i++) {
        // 先走两步
        int x = p.first, y = p.second;
        x += 2 * offset[i][0], y += 2 * offset[i][1];
        // 向左转60度和向右转60度
        int d1 = (i + 1) % 6, d2 = (i + 5) % 6;
        int n1 = pointToId[{x + offset[d1][0], y + offset[d1][1]}];
        int n2 = pointToId[{x + offset[d2][0], y + offset[d2][1]}];
        if (n1 <= N) moves.push_back(n1);
        if (n2 <= N) moves.push_back(n2);
    }
    return moves;
}

int main() {
    int N, M;
    initialize(); // 预计算坐标映射
    while (cin >> N >> M) {
        vector<bool> obstacle(N + 1, false);
        vector<int> dist(N + 1, INF);
        // 读取障碍物
        for (int i = 0; i < M; ++i) {
            int x;
            cin >> x;
            if (x >= 1 && x <= N) obstacle[x] = true;
        }
        int start, target;
        cin >> start >> target;
       
        // BFS求最短路径
        queue<int> q;
        if (start >= 1 && start <= N && !obstacle[start]) {
            dist[start] = 0;
            q.push(start);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == target) break; // 到达终点
            vector<int> nextMoves = getKnightMoves(u, N);
            for (int next : nextMoves)
                if (next >= 1 && next <= N && !obstacle[next] && dist[next] == INF) {
                    dist[next] = dist[u] + 1;
                    q.push(next);
                }
        }
        if (dist[target] == INF) cout << "Impossible.";
        else cout << dist[target];
        cout << '\n';
    }
    return 0;
}
