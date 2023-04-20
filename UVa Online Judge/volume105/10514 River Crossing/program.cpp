// River Crossing
// UVa ID: 10514
// Verdict: Accepted
// Submission Date: 2023-04-20
// UVa Run Time: 0.040s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
} ps[1100];

double norm(point a) { return a.x * a.x + a.y * a.y; }
double abs(point a) { return sqrt(norm(a)); }
double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double cross(point a, point b) { return a.x * b.y - a.y * b.x; }

struct segment {
    point p1, p2;
};

double getDistPL(point p, segment l) {
	return fabs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1));
}

double getDistPS(point p, segment s) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
    return getDistPL(p, s);
}

double getDistSS(segment s1, segment s2) {
	return min(min(getDistPS(s2.p1, s1), getDistPS(s2.p2, s1)),
	    min(getDistPS(s1.p1, s2), getDistPS(s1.p2, s2)));
}

struct edge {
    int v;
    double w;
    int nxt;
    bool operator<(const edge &e) const { return w > e.w; }
} g[10010];

int head[110], ecnt;

void addEdge(int u, int v, double w) {
    g[ecnt] = edge{v, w, head[u]};
    head[u] = ecnt++;
    g[ecnt] = edge{u, w, head[v]};
    head[v] = ecnt++;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, r1, r2, n;
    cin >> T;
    while (T--) {
        cin >> r1 >> r2 >> n;
        for (int i = 0; i < r1; i++) cin >> ps[i].x >> ps[i].y;
        for (int i = 0; i < r2; i++) cin >> ps[r1 + i].x >> ps[r1 + i].y;
        vector<point> pg[12];
        for (int i = 0, m; i < n; i++) {
            cin >> m;
            for (int j = 0, x, y; j < m; j++) {
                cin >> x >> y;
                pg[i].push_back(point(x, y));
            }
        }
        memset(head, -1, sizeof head);
        ecnt = 0;

        double mind = 1e10;
        for (int i = 0; i < r1 - 1; i++) {
            segment s1 = segment{ps[i], ps[i + 1]};
            for (int j = 0; j < r2 - 1; j++) {
                segment s2 = segment{ps[r1 + j], ps[r1 + j + 1]};
                mind = min(mind, getDistSS(s1, s2));
            }
        }
        addEdge(0, 1, mind);

        for (int i = 0; i < r1 - 1; i++) {
            segment s1 = segment{ps[i], ps[i + 1]};
            for (int j = 0; j < n; j++) {
                mind = 1e10;
                for (int k = 0; k < (int)pg[j].size(); k++) {
                    segment s2 = segment{pg[j][k], pg[j][(k + 1) % pg[j].size()]};
                    mind = min(mind, getDistSS(s1, s2));
                }
                addEdge(0, 2 + j, mind);
            }
        }

        for (int i = 0; i < r2 - 1; i++) {
            segment s1 = segment{ps[r1 + i], ps[r1 + i + 1]};
            for (int j = 0; j < n; j++) {
                mind = 1e10;
                for (int k = 0; k < (int)pg[j].size(); k++) {
                    segment s2 = segment{pg[j][k], pg[j][(k + 1) % pg[j].size()]};
                    mind = min(mind, getDistSS(s1, s2));
                }
                addEdge(1, 2 + j, mind);
            }
        }

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                mind = 1e10;
                for (int k = 0; k < pg[i].size(); k++) {
                    segment s1 = segment{pg[i][k], pg[i][(k + 1) % pg[i].size()]};
                    for (int l = 0; l < pg[j].size(); l++) {
                        segment s2 = segment{pg[j][l], pg[j][(l + 1) % pg[j].size()]};
                        mind = min(mind, getDistSS(s1, s2));
                    }
                }
                addEdge(2 + i, 2 + j, mind);
            }
        double d[110];
        priority_queue<edge> q;
        q.push(edge{0, 0, 0});
        for (int i = 0; i < 100; i++) d[i] = 1e10;
        d[0] = 0;
        while (!q.empty()) {
            edge e = q.top(); q.pop();
            for (int i = head[e.v]; ~i; i = g[i].nxt) {
                if (d[g[i].v] > e.w + g[i].w) {
                    d[g[i].v] = e.w + g[i].w;
                    q.push(edge{g[i].v, d[g[i].v], 0});
                }
            }
        }
        cout << fixed << setprecision(3) << d[1] << '\n';
    }

    return 0;
}
