#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

struct Node {
    int dis, id, dir;
    bool operator < (const Node &other) const {
        return dis > other.dis;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, r1, c1, r2, c2, caseNum = 0;
    while (cin >> n >> m >> r1 >> c1 >> r2 >> c2) {
        vector<vector<int>> cost(n, vector<int>(m, -1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                string s;
                cin >> s;
                if (s != "*") cost[i][j] = stoi(s);
            }
        }
        int sr = r1 - 1, sc = c1 - 1, tr = r2 - 1, tc = c2 - 1;
        int startId = sr * m + sc, targetId = tr * m + tc;
        int normalAns = -1, turnAns = -1;
        vector<int> normalDist(n * m, inf);
        priority_queue<Node> heap;
        normalDist[startId] = cost[sr][sc];
        heap.push({normalDist[startId], startId, -1});
        while (!heap.empty()) {
            Node cur = heap.top();
            heap.pop();
            if (cur.dis != normalDist[cur.id]) continue;
            if (cur.id == targetId) break;
            int r = cur.id / m, c = cur.id % m;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m || cost[nr][nc] == -1) continue;
                int nextId = nr * m + nc;
                int nextDis = cur.dis + cost[nr][nc];
                if (nextDis < normalDist[nextId]) {
                    normalDist[nextId] = nextDis;
                    heap.push({nextDis, nextId, -1});
                }
            }
        }
        if (normalDist[targetId] != inf) normalAns = normalDist[targetId];
        if (startId == targetId) {
            turnAns = cost[sr][sc];
        } else {
            vector<array<int, 4>> turnDist(n * m);
            for (auto &item : turnDist) item.fill(inf);
            while (!heap.empty()) heap.pop();
            for (int d = 0; d < 4; d++) {
                int nr = sr + dr[d], nc = sc + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m || cost[nr][nc] == -1) continue;
                int nextId = nr * m + nc;
                int nextDis = cost[sr][sc] + cost[nr][nc];
                if (nextDis < turnDist[nextId][d]) {
                    turnDist[nextId][d] = nextDis;
                    heap.push({nextDis, nextId, d});
                }
            }
            while (!heap.empty()) {
                Node cur = heap.top();
                heap.pop();
                if (cur.dis != turnDist[cur.id][cur.dir]) continue;
                int r = cur.id / m, c = cur.id % m;
                for (int d = 0; d < 4; d++) {
                    if (d == cur.dir) continue;
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m || cost[nr][nc] == -1) continue;
                    int nextId = nr * m + nc;
                    int nextDis = cur.dis + cost[nr][nc];
                    if (nextDis < turnDist[nextId][d]) {
                        turnDist[nextId][d] = nextDis;
                        heap.push({nextDis, nextId, d});
                    }
                }
            }
            turnAns = inf;
            for (int d = 0; d < 4; d++) turnAns = min(turnAns, turnDist[targetId][d]);
            if (turnAns == inf) turnAns = -1;
        }
        cout << "Case " << ++caseNum << ": " << normalAns << ' ' << turnAns << '\n';
    }
    return 0;
}
