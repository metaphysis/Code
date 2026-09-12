#include <bits/stdc++.h>
using namespace std;

const long double Eps = 1e-10L;

struct Point {
    long double x, y;
};

struct Edge {
    int from, to, rev;
};

struct Dsu {
    vector<int> fa;
    Dsu(int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) fa[y] = x;
    }
};

long double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long double disToSegment(Point p, Point a, Point b) {
    long double dx = b.x - a.x, dy = b.y - a.y;
    long double len2 = dx * dx + dy * dy;
    long double t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / len2;
    t = max(0.0L, min(1.0L, t));
    Point q = {a.x + t * dx, a.y + t * dy};
    long double px = p.x - q.x, py = p.y - q.y;
    return px * px + py * py;
}

bool pointInPolygon(Point p, const vector<Point> &poly) {
    bool in = false;
    int n = poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        Point a = poly[i], b = poly[j];
        bool up = a.y > p.y;
        bool down = b.y > p.y;
        if (up != down) {
            long double x = a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y);
            if (x > p.x) in = !in;
        }
    }
    return in;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<Point> capitals(n);
        for (int i = 0; i < n; i++) {
            long double x, y;
            cin >> x >> y;
            capitals[i] = {x, y};
        }
        vector<Point> points;
        vector<Edge> edges;
        vector<pair<int, int>> undirected;
        map<pair<long double, long double>, int> pointId;
        auto getPointId = [&](Point p) {
            pair<long double, long double> key = {p.x, p.y};
            auto it = pointId.find(key);
            if (it != pointId.end()) return it->second;
            int id = points.size();
            pointId[key] = id;
            points.push_back(p);
            return id;
        };
        for (int i = 0; i < m; i++) {
            long double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int u = getPointId({x1, y1}), v = getPointId({x2, y2});
            int id = edges.size();
            edges.push_back({u, v, id + 1});
            edges.push_back({v, u, id});
            undirected.push_back({id, id + 1});
        }
        int vertexCount = points.size();
        vector<vector<int>> out(vertexCount);
        for (int i = 0; i < (int)edges.size(); i++) out[edges[i].from].push_back(i);
        for (int i = 0; i < vertexCount; i++) {
            sort(out[i].begin(), out[i].end(), [&](int a, int b) {
                Point pa = points[edges[a].to], pb = points[edges[b].to], pc = points[edges[a].from];
                long double aa = atan2(pa.y - pc.y, pa.x - pc.x);
                long double ab = atan2(pb.y - pc.y, pb.x - pc.x);
                return aa < ab;
            });
        }
        vector<int> pos(edges.size());
        for (int i = 0; i < vertexCount; i++)
            for (int j = 0; j < (int)out[i].size(); j++)
                pos[out[i][j]] = j;
        vector<int> nextEdge(edges.size());
        for (int i = 0; i < (int)edges.size(); i++) {
            int v = edges[i].to, rev = edges[i].rev;
            int sz = out[v].size();
            int p = pos[rev];
            nextEdge[i] = out[v][(p - 1 + sz) % sz];
        }
        vector<int> faceId(edges.size(), -1);
        vector<vector<int>> faces;
        vector<long double> areas;
        for (int i = 0; i < (int)edges.size(); i++) {
            if (faceId[i] != -1) continue;
            int id = faces.size(), cur = i;
            vector<int> face;
            long double area = 0;
            do {
                faceId[cur] = id;
                face.push_back(cur);
                Point a = points[edges[cur].from], b = points[edges[cur].to];
                area += a.x * b.y - a.y * b.x;
                cur = nextEdge[cur];
            } while (cur != i);
            faces.push_back(face);
            areas.push_back(area / 2.0L);
        }
        int faceCount = faces.size();
        vector<vector<Point>> polygons(faceCount);
        vector<Point> samples(faceCount);
        for (int i = 0; i < faceCount; i++) {
            for (int e : faces[i]) polygons[i].push_back(points[edges[e].from]);
            Point a = points[edges[faces[i][0]].from], b = points[edges[faces[i][0]].to];
            long double dx = b.x - a.x, dy = b.y - a.y;
            long double len = sqrt(dx * dx + dy * dy);
            long double sign = areas[i] > 0 ? 1.0L : -1.0L;
            long double nx = -dy / len * sign, ny = dx / len * sign;
            samples[i] = {(a.x + b.x) / 2.0L + nx * 1e-7L, (a.y + b.y) / 2.0L + ny * 1e-7L};
        }
        Dsu dsu(faceCount);
        for (int i = 0; i < faceCount; i++) {
            int parent = -1;
            long double bestArea = 1e100L;
            for (int j = 0; j < faceCount; j++) {
                if (i == j || fabsl(areas[j]) <= fabsl(areas[i])) continue;
                if (!pointInPolygon(samples[i], polygons[j])) continue;
                if (fabsl(areas[j]) < bestArea) {
                    bestArea = fabsl(areas[j]);
                    parent = j;
                }
            }
            if (parent != -1 && areas[parent] > 0 && areas[i] < 0) dsu.unite(parent, i);
        }
        vector<int> faceState(faceCount, -1);
        for (int i = 0; i < n; i++) {
            int bestEdge = -1;
            long double bestDis = 1e100L;
            for (int j = 0; j < m; j++) {
                int e = undirected[j].first;
                Point a = points[edges[e].from], b = points[edges[e].to];
                long double dis = disToSegment(capitals[i], a, b);
                if (dis < bestDis) {
                    bestDis = dis;
                    bestEdge = e;
                }
            }
            Point a = points[edges[bestEdge].from], b = points[edges[bestEdge].to];
            if (cross(a, b, capitals[i]) > 0) faceState[dsu.find(faceId[bestEdge])] = i;
            else faceState[dsu.find(faceId[edges[bestEdge].rev])] = i;
        }
        vector<set<int>> enemy(n);
        for (int i = 0; i < m; i++) {
            int e1 = undirected[i].first, e2 = undirected[i].second;
            int f1 = faceState[dsu.find(faceId[e1])], f2 = faceState[dsu.find(faceId[e2])];
            if (f1 != -1 && f2 != -1 && f1 != f2) {
                enemy[f1].insert(f2);
                enemy[f2].insert(f1);
            }
        }
        for (int i = 0; i < n; i++) {
            cout << enemy[i].size();
            for (int x : enemy[i]) cout << ' ' << x + 1;
            cout << '\n';
        }
    }
    return 0;
}
