// Steam Roller
// UVa ID: 1078
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.150s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// 方向：0-停止, 1-上, 2-下, 3-左, 4-右
int dr[] = {0, -1, 1, 0, 0};
int dc[] = {0, 0, 0, -1, 1};

// 将坐标转换为唯一ID
inline int getId(int r, int c, int C) { return (r - 1) * C + c; }

struct State {
    int id, dir, cost;
    bool operator<(const State& other) const { return cost > other.cost; }
};

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int R, C, r1, c1, r2, c2, t;
    int caseNo = 1;
    while (cin >> R >> C >> r1 >> c1 >> r2 >> c2) {
        if (R == 0 && C == 0 && r1 == 0 && c1 == 0 && r2 == 0 && c2 == 0) break;
        // 使用map存储街道时间
        map<pair<int, int>, int> streetTime;
        // 按照题目描述的交替格式读取
        for (int i = 1; i <= R; i++) {
            // 读取第i行的横向街道（C-1个）
            for (int j = 1; j < C; j++) {
                cin >> t;
                if (t > 0) {
                    int id1 = getId(i, j, C), id2 = getId(i, j + 1, C);
                    streetTime[{id1, id2}] = streetTime[{id2, id1}] = t;
                }
            }
            // 如果不是最后一行，读取第i行的纵向街道（C个）
            if (i < R) {
                for (int j = 1; j <= C; j++) {
                    cin >> t;
                    if (t > 0) {
                        int id1 = getId(i, j, C), id2 = getId(i + 1, j, C);
                        streetTime[{id1, id2}] = streetTime[{id2, id1}] = t;
                    }
                }
            }
        }
        int startId = getId(r1, c1, C), endId = getId(r2, c2, C);
        // 距离数组：dist[id][dir]
        vector<vector<int>> dist(R * C + 5, vector<int>(5, INF));
        priority_queue<State> pq;
        dist[startId][0] = 0;
        pq.push({startId, 0, 0});
        int answer = INF;
        while (!pq.empty()) {
            State cur = pq.top(); pq.pop();
            int id = cur.id, dir = cur.dir, cost = cur.cost;
            // 将id转换回坐标
            int r = (id - 1) / C + 1, c = (id - 1) % C + 1;
            // 到达终点，必须是停止状态
            if (id == endId && dir == 0) {
                answer = min(answer, cost);
                continue;
            }
            // 尝试四个方向
            for (int ndir = 1; ndir <= 4; ndir++) {
                int nr = r + dr[ndir], nc = c + dc[ndir];
                if (nr < 1 || nr > R || nc < 1 || nc > C) continue;
                int nid = getId(nr, nc, C);
                // 检查街道是否存在
                auto it = streetTime.find({id, nid});
                if (it == streetTime.end()) continue;
                int timeNeeded = it->second;
                // 情况1：原来是停止，再次停止或者原来是运动，方向不变但停止
                int newCost = cost + 2 * timeNeeded;
                if ((dir == 0 || dir == ndir) && newCost < dist[nid][0]) {
                    dist[nid][0] = newCost;
                    pq.push({nid, 0, newCost});
                }
                // 情况2：从停止开始运动，到达交汇点不停止
                newCost = cost + 2 * timeNeeded;
                if (dir == 0 && newCost < dist[nid][ndir]) {
                    dist[nid][ndir] = newCost;
                    pq.push({nid, ndir, newCost});
                }
                // 情况3：继续之前的运动不停止
                newCost = cost + timeNeeded;
                if (dir == ndir && newCost < dist[nid][ndir]) {
                    dist[nid][ndir] = newCost;
                    pq.push({nid, ndir, newCost});
                }
            }
        }
        cout << "Case " << caseNo++ << ": ";
        if (answer == INF) cout << "Impossible" << endl;
        else cout << answer << '\n';
    }
    return 0;
}
