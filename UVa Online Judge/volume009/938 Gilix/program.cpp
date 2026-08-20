#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(const vector<vector<int>>& cost, int sx, int sy, bool fast) {
    int l = cost.size(), c = cost[0].size(), n = l * c, inf = INT_MAX;
    vector<int> dist(n, inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
    int start = sx * c + sy;
    dist[start] = 0;
    que.push({0, start});
    while (!que.empty()) {
        pair<int, int> cur = que.top();
        que.pop();
        int dis = cur.first, id = cur.second;
        if (dis != dist[id]) continue;
        int x = id / c, y = id % c;
        int dy = x % 2 == 0 ? -1 : 1;
        int dx[6] = {0, 0, -1, -1, 1, 1};
        int dc[6] = {-1, 1, 0, dy, 0, dy};
        for (int i = 0; i < 6; i++) {
            int nx = x + dx[i], ny = y + dc[i];
            if (nx < 0 || nx >= l) continue;
            ny = (ny + c) % c;
            int nid = nx * c + ny;
            int weight = fast ? cost[nx][ny] / 2 : cost[nx][ny];
            int nd = dis + weight;
            if (nd < dist[nid]) {
                dist[nid] = nd;
                que.push({nd, nid});
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l, c;
    cin >> l >> c;
    vector<vector<int>> cost(l, vector<int>(c));
    for (int i = 0; i < l; i++)
        for (int j = 0; j < c; j++)
            cin >> cost[i][j];
    int sx, sy, tx, ty, px, py;
    cin >> sx >> sy;
    cin >> tx >> ty;
    cin >> px >> py;
    vector<int> before = dijkstra(cost, sx, sy, false);
    vector<int> after = dijkstra(cost, px, py, true);
    int potionId = px * c + py, targetId = tx * c + ty;
    cout << before[potionId] + after[targetId] << '\n';
    return 0;
}
