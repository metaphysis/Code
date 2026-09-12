#include <bits/stdc++.h>
using namespace std;

struct Building {
    long long lx, ly, rx, ry;
};

struct Point {
    long long x, y;
};

bool inClosed(const Point &p, const Building &b) {
    return b.lx <= p.x && p.x <= b.rx && b.ly <= p.y && p.y <= b.ry;
}

bool inOpen(const Point &p, const Building &b) {
    return b.lx < p.x && p.x < b.rx && b.ly < p.y && p.y < b.ry;
}

bool canWalk(const Point &a, const Point &b, const vector<Building> &buildings) {
    if (a.y == b.y) {
        long long left = min(a.x, b.x), right = max(a.x, b.x);
        for (const Building &building : buildings)
            if (inOpen({a.x, a.y}, building) || inOpen({b.x, b.y}, building))
                return false;
        for (int i = 0; i < (int)buildings.size(); i++)
            for (int j = i + 1; j < (int)buildings.size(); j++) {
                long long lx = max(buildings[i].lx, buildings[j].lx);
                long long rx = min(buildings[i].rx, buildings[j].rx);
                long long ly = max(buildings[i].ly, buildings[j].ly);
                long long ry = min(buildings[i].ry, buildings[j].ry);
                if (ly == ry && max(left, lx) < min(right, rx) && a.y == ly)
                    return false;
            }
        for (const Building &building : buildings)
            if (a.y > building.ly && a.y < building.ry && max(left, building.lx) < min(right, building.rx))
                return false;
    } else {
        long long down = min(a.y, b.y), up = max(a.y, b.y);
        for (const Building &building : buildings)
            if (inOpen({a.x, a.y}, building) || inOpen({b.x, b.y}, building))
                return false;
        for (int i = 0; i < (int)buildings.size(); i++)
            for (int j = i + 1; j < (int)buildings.size(); j++) {
                long long lx = max(buildings[i].lx, buildings[j].lx);
                long long rx = min(buildings[i].rx, buildings[j].rx);
                long long ly = max(buildings[i].ly, buildings[j].ly);
                long long ry = min(buildings[i].ry, buildings[j].ry);
                if (lx == rx && max(down, ly) < min(up, ry) && a.x == lx)
                    return false;
            }
        for (const Building &building : buildings)
            if (a.x > building.lx && a.x < building.rx && max(down, building.ly) < min(up, building.ry))
                return false;
    }
    return true;
}

void addEdge(vector<vector<pair<int, int>>> &graph, int u, int v, int dir) {
    graph[u].push_back({v, dir});
    graph[v].push_back({u, dir});
}

int solve() {
    long long sx, sy, tx, ty;
    while (cin >> sx >> sy >> tx >> ty) {
        if (sx == 0 && sy == 0 && tx == 0 && ty == 0)
            break;
        int n;
        cin >> n;
        vector<Building> buildings(n);
        vector<long long> xs, ys;
        xs.push_back(sx);
        xs.push_back(tx);
        ys.push_back(sy);
        ys.push_back(ty);
        for (Building &building : buildings) {
            long long x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            building.lx = min(x1, x2);
            building.rx = max(x1, x2);
            building.ly = min(y1, y2);
            building.ry = max(y1, y2);
            xs.push_back(building.lx);
            xs.push_back(building.rx);
            ys.push_back(building.ly);
            ys.push_back(building.ry);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        int xn = xs.size(), yn = ys.size(), total = xn * yn;
        vector<Point> points(total);
        vector<vector<int>> id(xn, vector<int>(yn, -1));
        for (int i = 0; i < xn; i++)
            for (int j = 0; j < yn; j++) {
                int index = i * yn + j;
                points[index] = {xs[i], ys[j]};
                int cnt = 0;
                for (const Building &building : buildings)
                    if (inClosed(points[index], building))
                        cnt++;
                if (cnt <= 1)
                    id[i][j] = index;
            }
        vector<vector<pair<int, int>>> graph(total);
        for (int i = 0; i < xn; i++)
            for (int j = 0; j < yn; j++) {
                int u = id[i][j];
                if (u == -1)
                    continue;
                if (i + 1 < xn && id[i + 1][j] != -1) {
                    int v = id[i + 1][j];
                    if (canWalk(points[u], points[v], buildings))
                        addEdge(graph, u, v, 0);
                }
                if (j + 1 < yn && id[i][j + 1] != -1) {
                    int v = id[i][j + 1];
                    if (canWalk(points[u], points[v], buildings))
                        addEdge(graph, u, v, 1);
                }
            }
        int sxId = lower_bound(xs.begin(), xs.end(), sx) - xs.begin();
        int syId = lower_bound(ys.begin(), ys.end(), sy) - ys.begin();
        int txId = lower_bound(xs.begin(), xs.end(), tx) - xs.begin();
        int tyId = lower_bound(ys.begin(), ys.end(), ty) - ys.begin();
        int start = id[sxId][syId], target = id[txId][tyId];
        const int inf = 1e9;
        vector<vector<int>> dist(total, vector<int>(2, inf));
        deque<pair<int, int>> que;
        dist[start][0] = 0;
        dist[start][1] = 0;
        que.push_back({start, 0});
        que.push_back({start, 1});
        while (!que.empty()) {
            int u = que.front().first, lastDir = que.front().second;
            que.pop_front();
            for (const auto &edge : graph[u]) {
                int v = edge.first, nextDir = edge.second;
                int cost = lastDir == nextDir ? 0 : 1;
                if (dist[v][nextDir] > dist[u][lastDir] + cost) {
                    dist[v][nextDir] = dist[u][lastDir] + cost;
                    if (cost == 0)
                        que.push_front({v, nextDir});
                    else
                        que.push_back({v, nextDir});
                }
            }
        }
        int answer = min(dist[target][0], dist[target][1]);
        cout << (answer == inf ? -1 : answer) << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
