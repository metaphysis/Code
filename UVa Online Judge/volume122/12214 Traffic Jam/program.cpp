#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

Point sub(Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double getLen(Point a) {
    return sqrt(dot(a, a));
}

Point getNormal(Point a) {
    double len = getLen(a);
    return Point(-a.y / len, a.x / len);
}

Point rotate(Point a, double ang) {
    double c = cos(ang), s = sin(ang);
    return Point(a.x * c - a.y * s, a.x * s + a.y * c);
}

bool onSegment(Point p, Point a, Point b) {
    return fabs(cross(sub(a, p), sub(b, p))) < eps && dot(sub(a, p), sub(b, p)) <= eps;
}

double getLineT(Point a, Point v, Point p, Point w) {
    return cross(sub(p, a), w) / cross(v, w);
}

vector<Point> getPoints(vector<Point> pts, int segCnt, int fuel) {
    double ang = asin(1.0 / fuel);
    for (int i = 0; i <= segCnt; i++) {
        for (int j = 0; j < segCnt; j++) {
            Point v = sub(pts[j + 1], pts[j]);
            Point normal = getNormal(v);
            Point up = rotate(normal, ang), down = rotate(normal, -ang);
            double den1 = cross(v, up), den2 = cross(v, down);
            if (fabs(den1) >= eps) {
                double t = getLineT(pts[j], v, pts[i], up);
                if (t >= -eps && t <= 1.0 + eps) pts.push_back(Point(pts[j].x + v.x * t, pts[j].y + v.y * t));
            }
            if (fabs(den2) >= eps) {
                double t = getLineT(pts[j], v, pts[i], down);
                if (t >= -eps && t <= 1.0 + eps) pts.push_back(Point(pts[j].x + v.x * t, pts[j].y + v.y * t));
            }
        }
    }
    return pts;
}

double dijkstra(const vector<vector<double>>& graph, int s, int t) {
    int n = graph.size();
    vector<double> dis(n, 1e100);
    vector<int> vis(n, 0);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    dis[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int v = 0; v < n; v++) {
            double nd = dis[u] + graph[u][v];
            if (nd + eps < dis[v]) {
                dis[v] = nd;
                pq.push({dis[v], v});
            }
        }
    }
    return dis[t];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, fuel, tc = 0;
    while (cin >> n >> fuel && (n || fuel)) {
        vector<Point> road(n + 1);
        for (int i = 0; i <= n; i++) cin >> road[i].x >> road[i].y;
        vector<Point> pts = getPoints(road, n, fuel);
        int m = pts.size();
        vector<vector<double>> graph(m, vector<double>(m, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) graph[i][j] = fuel * getLen(sub(pts[i], pts[j]));
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < m; i++) {
                if (!onSegment(pts[i], road[k], road[k + 1])) continue;
                for (int j = 0; j < m; j++) {
                    if (!onSegment(pts[j], road[k], road[k + 1])) continue;
                    double di = getLen(sub(pts[i], road[k]));
                    double dj = getLen(sub(pts[j], road[k]));
                    if (dj <= di + eps) graph[j][i] = min(graph[j][i], getLen(sub(pts[i], pts[j])));
                }
            }
        }
        cout << fixed << setprecision(3);
        cout << "Case " << ++tc << ": " << dijkstra(graph, 0, n) << '\n';
    }
    return 0;
}
