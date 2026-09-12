#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

struct Point {
    double x, y;
};

Point operator + (const Point &a, const Point &b) { return {a.x + b.x, a.y + b.y}; }
Point operator - (const Point &a, const Point &b) { return {a.x - b.x, a.y - b.y}; }
Point operator * (const Point &a, double k) { return {a.x * k, a.y * k}; }

double cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
double cross(const Point &a, const Point &b, const Point &c) { return cross(b - a, c - a); }
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

int sgn(double x) {
    if (x > eps) return 1;
    if (x < -eps) return -1;
    return 0;
}

bool samePt(const Point &a, const Point &b) {
    return fabs(a.x - b.x) <= eps && fabs(a.y - b.y) <= eps;
}

bool onSeg(const Point &a, const Point &b, const Point &p) {
    return sgn(cross(a, b, p)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}

bool properCross(const Point &a, const Point &b, const Point &c, const Point &d) {
    int o1 = sgn(cross(a, b, c)), o2 = sgn(cross(a, b, d));
    int o3 = sgn(cross(c, d, a)), o4 = sgn(cross(c, d, b));
    return o1 * o2 < 0 && o3 * o4 < 0;
}

Point lineInter(const Point &a, const Point &b, const Point &c, const Point &d) {
    Point r = b - a, s = d - c;
    double t = cross(c - a, s) / cross(r, s);
    return a + r * t;
}

double paramOnSeg(const Point &a, const Point &b, const Point &p) {
    if (fabs(a.x - b.x) >= fabs(a.y - b.y)) return (p.x - a.x) / (b.x - a.x);
    return (p.y - a.y) / (b.y - a.y);
}

int getPointId(const Point &p, vector<Point> &pts) {
    for (int i = 0; i < (int)pts.size(); i++)
        if (samePt(pts[i], p)) return i;
    pts.push_back(p);
    return (int)pts.size() - 1;
}

bool inPoly(const Point &p, const vector<Point> &poly) {
    bool in = false;
    int n = (int)poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (onSeg(a, b, p)) return true;
        if ((a.y > p.y) != (b.y > p.y)) {
            double x = (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x;
            if (x > p.x + eps) in = !in;
        }
    }
    return in;
}

vector<int> reduceCycle(const vector<int> &seq, const vector<Point> &pts) {
    vector<int> cur = seq;
    while (true) {
        int n = (int)cur.size();
        if (n < 3) break;
        vector<int> nxt;
        bool changed = false;
        for (int i = 0; i < n; i++) {
            int a = cur[(i - 1 + n) % n], b = cur[i], c = cur[(i + 1) % n];
            if (fabs(cross(pts[a], pts[b], pts[c])) <= eps) changed = true;
            else nxt.push_back(b);
        }
        cur.swap(nxt);
        if (!changed) break;
    }
    return cur;
}

double polyArea(const vector<int> &seq, const vector<Point> &pts) {
    double s = 0;
    int n = (int)seq.size();
    for (int i = 0; i < n; i++) s += cross(pts[seq[i]], pts[seq[(i + 1) % n]]);
    return s * 0.5;
}

vector<int> rotateToMin(const vector<int> &seq, const vector<Point> &pts) {
    int n = (int)seq.size(), pos = 0;
    for (int i = 1; i < n; i++) {
        Point a = pts[seq[i]], b = pts[seq[pos]];
        if (a.x < b.x - eps || (fabs(a.x - b.x) <= eps && a.y < b.y - eps)) pos = i;
    }
    vector<int> res;
    for (int i = 0; i < n; i++) res.push_back(seq[(pos + i) % n]);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);
    int n1, n2, ds = 1;
    while (cin >> n1) {
        if (n1 == 0) break;
        vector<Point> p1(n1), p2;
        for (int i = 0; i < n1; i++) cin >> p1[i].x >> p1[i].y;
        cin >> n2;
        p2.resize(n2);
        for (int i = 0; i < n2; i++) cin >> p2[i].x >> p2[i].y;
        vector<Point> pts;
        vector<int> id1(n1), id2(n2);
        for (int i = 0; i < n1; i++) id1[i] = getPointId(p1[i], pts);
        for (int i = 0; i < n2; i++) id2[i] = getPointId(p2[i], pts);
        int ec = n1 + n2;
        vector<vector<pair<double, int> > > cut(ec);
        vector<int> own(ec);
        for (int i = 0; i < n1; i++) {
            int j = (i + 1) % n1;
            own[i] = 0;
            cut[i].push_back({0.0, id1[i]});
            cut[i].push_back({1.0, id1[j]});
        }
        for (int i = 0; i < n2; i++) {
            int j = (i + 1) % n2;
            int id = n1 + i;
            own[id] = 1;
            cut[id].push_back({0.0, id2[i]});
            cut[id].push_back({1.0, id2[j]});
        }
        for (int i = 0; i < n1; i++) {
            Point a = p1[i], b = p1[(i + 1) % n1];
            for (int j = 0; j < n2; j++) {
                Point c = p2[j], d = p2[(j + 1) % n2];
                if (onSeg(a, b, c)) cut[i].push_back({paramOnSeg(a, b, c), id2[j]});
                if (onSeg(a, b, d)) cut[i].push_back({paramOnSeg(a, b, d), id2[(j + 1) % n2]});
                if (onSeg(c, d, a)) cut[n1 + j].push_back({paramOnSeg(c, d, a), id1[i]});
                if (onSeg(c, d, b)) cut[n1 + j].push_back({paramOnSeg(c, d, b), id1[(i + 1) % n1]});
                if (properCross(a, b, c, d)) {
                    Point p = lineInter(a, b, c, d);
                    int id = getPointId(p, pts);
                    cut[i].push_back({paramOnSeg(a, b, p), id});
                    cut[n1 + j].push_back({paramOnSeg(c, d, p), id});
                }
            }
        }
        set<pair<int, int> > used;
        vector<pair<int, int> > undirected;
        auto addEdge = [&](int u, int v) {
            if (u == v) return;
            pair<int, int> key = minmax(u, v);
            if (used.insert(key).second) undirected.push_back({u, v});
        };
        for (int i = 0; i < ec; i++) {
            sort(cut[i].begin(), cut[i].end(), [](const pair<double, int> &a, const pair<double, int> &b) {
                if (fabs(a.first - b.first) > eps) return a.first < b.first;
                return a.second < b.second;
            });
            vector<int> seq;
            for (int j = 0; j < (int)cut[i].size(); j++)
                if (seq.empty() || seq.back() != cut[i][j].second) seq.push_back(cut[i][j].second);
            for (int j = 0; j + 1 < (int)seq.size(); j++) {
                Point m = (pts[seq[j]] + pts[seq[j + 1]]) * 0.5;
                if (own[i] == 0) {
                    if (inPoly(m, p2)) addEdge(seq[j], seq[j + 1]);
                } else {
                    if (inPoly(m, p1)) addEdge(seq[j], seq[j + 1]);
                }
            }
        }
        vector<int> from, to, rev, vis;
        vector<vector<int> > out(pts.size());
        for (int i = 0; i < (int)undirected.size(); i++) {
            int u = undirected[i].first, v = undirected[i].second;
            int id = (int)from.size();
            from.push_back(u);
            to.push_back(v);
            rev.push_back(id + 1);
            vis.push_back(0);
            from.push_back(v);
            to.push_back(u);
            rev.push_back(id);
            vis.push_back(0);
            out[u].push_back(id);
            out[v].push_back(id + 1);
        }
        vector<int> pos(from.size(), 0);
        for (int i = 0; i < (int)pts.size(); i++) {
            auto &lst = out[i];
            sort(lst.begin(), lst.end(), [&](int a, int b) {
                Point da = pts[to[a]] - pts[from[a]];
                Point db = pts[to[b]] - pts[from[b]];
                double aa = atan2(da.y, da.x), bb = atan2(db.y, db.x);
                if (fabs(aa - bb) > eps) return aa < bb;
                double la = dot(da, da), lb = dot(db, db);
                return la < lb;
            });
            for (int j = 0; j < (int)lst.size(); j++) pos[lst[j]] = j;
        }
        vector<vector<int> > res;
        for (int i = 0; i < (int)from.size(); i++) {
            if (vis[i]) continue;
            vector<int> seq;
            int cur = i;
            while (!vis[cur]) {
                vis[cur] = 1;
                seq.push_back(from[cur]);
                int v = to[cur];
                int twin = rev[cur];
                int deg = (int)out[v].size();
                int idx = pos[twin];
                cur = out[v][(idx - 1 + deg) % deg];
            }
            seq = reduceCycle(seq, pts);
            if ((int)seq.size() < 3) continue;
            if (polyArea(seq, pts) <= eps) continue;
            seq = rotateToMin(seq, pts);
            res.push_back(seq);
        }
        cout << "Data Set " << ds++ << "\n";
        cout << "Number of intersection regions: " << res.size() << "\n";
        for (int i = 0; i < (int)res.size(); i++) {
            cout << "Region " << i + 1 << ":";
            for (int id : res[i]) cout << "(" << pts[id].x << "," << pts[id].y << ")";
            cout << "\n";
        }
    }
    return 0;
}
