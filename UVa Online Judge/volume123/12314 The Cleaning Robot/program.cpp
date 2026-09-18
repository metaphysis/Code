#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double sideEps = 1e-6;
const double pi = acos(-1.0);

struct Point {
    double x, y;
    Point operator + (const Point &o) const {
        return {x + o.x, y + o.y};
    }
    Point operator - (const Point &o) const {
        return {x - o.x, y - o.y};
    }
    Point operator * (double k) const {
        return {x * k, y * k};
    }
    Point operator / (double k) const {
        return {x / k, y / k};
    }
};

struct SegPrim {
    Point a, b;
    vector<double> cuts;
};

struct CirPrim {
    Point c;
    vector<double> cuts;
};

struct Atom {
    int u, v, type;
    double len, area;
};

struct Dsu {
    vector<int> fa, sz;
    Dsu(int n) {
        fa.resize(n);
        sz.assign(n, 1);
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if (fa[x] != x) fa[x] = find(fa[x]);
        return fa[x];
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
    }
};

int n;
double robotR;
vector<Point> poly;

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double length(Point a) {
    return sqrt(dot(a, a));
}

double dist(Point a, Point b) {
    return length(a - b);
}

double clampVal(double x, double l, double r) {
    return max(l, min(r, x));
}

bool samePoint(Point a, Point b) {
    return dist(a, b) <= 1e-8;
}

double pointSegDist(Point p, Point a, Point b) {
    Point d = b - a;
    double l2 = dot(d, d);
    if (l2 <= eps) return dist(p, a);
    double t = clampVal(dot(p - a, d) / l2, 0.0, 1.0);
    return dist(p, a + d * t);
}

bool pointOnSeg(Point p, Point a, Point b) {
    if (fabs(cross(b - a, p - a)) > 1e-8) return false;
    return dot(p - a, p - b) <= 1e-8;
}

bool pointInPoly(Point p) {
    if (n < 3) return false;
    bool inside = false;
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (pointOnSeg(p, a, b)) return true;
        bool crossRay = (a.y > p.y) != (b.y > p.y);
        if (crossRay) {
            double x = a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y);
            if (x > p.x) inside = !inside;
        }
    }
    return inside;
}

double obstacleDist(Point p) {
    double ans = 1e100;
    if (n == 1) return dist(p, poly[0]);
    for (int i = 0; i < n; i++) ans = min(ans, pointSegDist(p, poly[i], poly[(i + 1) % n]));
    return ans;
}

bool isFeasible(Point p) {
    if (pointInPoly(p)) return false;
    return obstacleDist(p) >= robotR - 1e-7;
}

bool isOpenFree(Point p) {
    if (pointInPoly(p)) return false;
    return obstacleDist(p) > robotR + 1e-8;
}

void addCut(vector<double> &cuts, double t, double l, double r) {
    if (t < l - 1e-8 || t > r + 1e-8) return;
    cuts.push_back(clampVal(t, l, r));
}

void normalizeCuts(vector<double> &cuts) {
    sort(cuts.begin(), cuts.end());
    vector<double> res;
    for (double x : cuts) {
        if (res.empty() || fabs(x - res.back()) > 1e-9) res.push_back(x);
    }
    cuts.swap(res);
}

void intersectSegSeg(SegPrim &a, SegPrim &b) {
    Point da = a.b - a.a, db = b.b - b.a, dc = b.a - a.a;
    double cr = cross(da, db);
    if (fabs(cr) > eps) {
        double ta = cross(dc, db) / cr, tb = cross(dc, da) / cr;
        if (ta >= -eps && ta <= 1.0 + eps && tb >= -eps && tb <= 1.0 + eps) {
            addCut(a.cuts, ta, 0.0, 1.0);
            addCut(b.cuts, tb, 0.0, 1.0);
        }
        return;
    }
    if (fabs(cross(dc, da)) > 1e-8) return;
    double la = dot(da, da), lb = dot(db, db);
    if (la <= eps || lb <= eps) return;
    double ta1 = dot(b.a - a.a, da) / la, ta2 = dot(b.b - a.a, da) / la;
    double tb1 = dot(a.a - b.a, db) / lb, tb2 = dot(a.b - b.a, db) / lb;
    addCut(a.cuts, ta1, 0.0, 1.0);
    addCut(a.cuts, ta2, 0.0, 1.0);
    addCut(b.cuts, tb1, 0.0, 1.0);
    addCut(b.cuts, tb2, 0.0, 1.0);
}

void intersectSegCir(SegPrim &s, CirPrim &c) {
    Point d = s.b - s.a, f = s.a - c.c;
    double aa = dot(d, d), bb = 2.0 * dot(f, d), cc = dot(f, f) - robotR * robotR;
    double det = bb * bb - 4.0 * aa * cc;
    if (det < -eps || aa <= eps) return;
    det = max(0.0, det);
    double sd = sqrt(det), t1 = (-bb - sd) / (2.0 * aa), t2 = (-bb + sd) / (2.0 * aa);
    vector<double> ts = {t1, t2};
    for (double t : ts) {
        if (t < -eps || t > 1.0 + eps) continue;
        t = clampVal(t, 0.0, 1.0);
        Point p = s.a + d * t;
        double ang = atan2(p.y - c.c.y, p.x - c.c.x);
        if (ang < 0.0) ang += 2.0 * pi;
        addCut(s.cuts, t, 0.0, 1.0);
        c.cuts.push_back(ang);
    }
}

void intersectCirCir(CirPrim &a, CirPrim &b) {
    Point dVec = b.c - a.c;
    double d = length(dVec);
    if (d <= eps || d > 2.0 * robotR + eps) return;
    double x = d / 2.0, h2 = robotR * robotR - x * x;
    if (h2 < -eps) return;
    double h = sqrt(max(0.0, h2));
    Point dir = dVec / d, per = {-dir.y, dir.x};
    Point base = a.c + dir * x;
    vector<Point> ps = {base + per * h, base - per * h};
    for (Point p : ps) {
        double aa = atan2(p.y - a.c.y, p.x - a.c.x), ab = atan2(p.y - b.c.y, p.x - b.c.x);
        if (aa < 0.0) aa += 2.0 * pi;
        if (ab < 0.0) ab += 2.0 * pi;
        a.cuts.push_back(aa);
        b.cuts.push_back(ab);
    }
}

pair<long long, long long> pointKey(Point p) {
    const double scale = 1e8;
    return {llround(p.x * scale), llround(p.y * scale)};
}

array<long long, 4> segKey(Point a, Point b) {
    pair<long long, long long> ka = pointKey(a), kb = pointKey(b);
    if (kb < ka) swap(ka, kb);
    return {ka.first, ka.second, kb.first, kb.second};
}

int getNode(Point p, map<pair<long long, long long>, int> &nodeMap, vector<Point> &nodes) {
    pair<long long, long long> key = pointKey(p);
    auto it = nodeMap.find(key);
    if (it != nodeMap.end()) return it->second;
    int id = nodes.size();
    nodeMap[key] = id;
    nodes.push_back(p);
    return id;
}

void addFeasibleNode(Point p, map<pair<long long, long long>, int> &nodeMap, vector<Point> &nodes) {
    if (isFeasible(p)) getNode(p, nodeMap, nodes);
}

double solveCase() {
    vector<SegPrim> segs;
    vector<CirPrim> cirs;
    set<pair<long long, long long>> cirSet;
    if (n >= 2) {
        for (int i = 0; i < n; i++) {
            Point a = poly[i], b = poly[(i + 1) % n], d = b - a;
            double len = length(d);
            if (len <= eps) continue;
            Point normal = {-d.y / len, d.x / len};
            segs.push_back({a + normal * robotR, b + normal * robotR, {0.0, 1.0}});
            segs.push_back({a - normal * robotR, b - normal * robotR, {0.0, 1.0}});
        }
    }
    for (Point p : poly) {
        pair<long long, long long> key = pointKey(p);
        if (cirSet.count(key)) continue;
        cirSet.insert(key);
        cirs.push_back({p, {0.0}});
    }
    for (int i = 0; i < (int)segs.size(); i++) {
        for (int j = i + 1; j < (int)segs.size(); j++) intersectSegSeg(segs[i], segs[j]);
    }
    for (int i = 0; i < (int)segs.size(); i++) {
        for (int j = 0; j < (int)cirs.size(); j++) intersectSegCir(segs[i], cirs[j]);
    }
    for (int i = 0; i < (int)cirs.size(); i++) {
        for (int j = i + 1; j < (int)cirs.size(); j++) intersectCirCir(cirs[i], cirs[j]);
    }
    for (SegPrim &s : segs) normalizeCuts(s.cuts);
    for (CirPrim &c : cirs) normalizeCuts(c.cuts);
    map<pair<long long, long long>, int> nodeMap;
    vector<Point> nodes;
    for (SegPrim &s : segs) {
        for (double t : s.cuts) addFeasibleNode(s.a + (s.b - s.a) * t, nodeMap, nodes);
    }
    for (CirPrim &c : cirs) {
        for (double ang : c.cuts) {
            Point p = c.c + Point{cos(ang), sin(ang)} * robotR;
            addFeasibleNode(p, nodeMap, nodes);
        }
    }
    vector<Atom> atoms;
    set<array<long long, 4>> usedSeg;
    for (SegPrim &s : segs) {
        Point dir = s.b - s.a;
        for (int i = 0; i + 1 < (int)s.cuts.size(); i++) {
            double t1 = s.cuts[i], t2 = s.cuts[i + 1];
            if (t2 - t1 <= eps) continue;
            Point a = s.a + dir * t1, b = s.a + dir * t2, mid = (a + b) / 2.0;
            if (!isFeasible(mid)) continue;
            array<long long, 4> key = segKey(a, b);
            if (usedSeg.count(key)) continue;
            usedSeg.insert(key);
            Point unit = (b - a) / length(b - a), left = {-unit.y, unit.x};
            bool lf = isOpenFree(mid + left * sideEps), rf = isOpenFree(mid - left * sideEps);
            if (lf && rf) continue;
            int u = getNode(a, nodeMap, nodes), v = getNode(b, nodeMap, nodes);
            double len = length(b - a);
            if (lf != rf) {
                double area = cross(a, b) / 2.0;
                if (!lf) area = -area;
                atoms.push_back({u, v, 1, len, area});
            } else {
                atoms.push_back({u, v, 2, len, 0.0});
            }
        }
    }
    for (CirPrim &c : cirs) {
        int m = c.cuts.size();
        for (int i = 0; i < m; i++) {
            double a1 = c.cuts[i], a2 = i + 1 < m ? c.cuts[i + 1] : c.cuts[0] + 2.0 * pi;
            double delta = a2 - a1;
            if (delta <= eps) continue;
            double am = (a1 + a2) / 2.0;
            Point p1 = c.c + Point{cos(a1), sin(a1)} * robotR;
            Point p2 = c.c + Point{cos(a2), sin(a2)} * robotR;
            Point mid = c.c + Point{cos(am), sin(am)} * robotR;
            if (!isFeasible(mid)) continue;
            Point left = {-cos(am), -sin(am)};
            bool lf = isOpenFree(mid + left * sideEps), rf = isOpenFree(mid - left * sideEps);
            if (lf && rf) continue;
            int u = getNode(p1, nodeMap, nodes), v = getNode(p2, nodeMap, nodes);
            double len = robotR * delta;
            if (lf != rf) {
                double area = (cross(c.c, p2 - p1) + robotR * robotR * delta) / 2.0;
                if (!lf) area = -area;
                atoms.push_back({u, v, 1, len, area});
            } else {
                atoms.push_back({u, v, 2, len, 0.0});
            }
        }
    }
    Dsu dsu(nodes.size());
    for (Atom &a : atoms) dsu.unite(a.u, a.v);
    vector<double> area(nodes.size(), 0.0), boundLen(nodes.size(), 0.0), degLen(nodes.size(), 0.0);
    vector<bool> exists(nodes.size(), false);
    for (int i = 0; i < (int)nodes.size(); i++) exists[dsu.find(i)] = true;
    for (Atom &a : atoms) {
        int rt = dsu.find(a.u);
        area[rt] += a.area;
        if (a.type == 1) boundLen[rt] += a.len;
        else degLen[rt] += a.len;
    }
    double ans = -1.0;
    for (int i = 0; i < (int)nodes.size(); i++) {
        if (dsu.find(i) != i || !exists[i]) continue;
        if (area[i] < -1e-7) continue;
        double cur = max(0.0, area[i]) + robotR * boundLen[i] + 2.0 * robotR * degLen[i] + pi * robotR * robotR;
        ans = max(ans, cur);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int inputR;
    while (cin >> n >> inputR) {
        if (n == 0 && inputR == 0) break;
        robotR = inputR;
        poly.resize(n);
        for (Point &p : poly) cin >> p.x >> p.y;
        double ans = solveCase();
        if (ans < 0.0) cout << "Impossible\n";
        else cout << fixed << setprecision(2) << ans + 1e-8 << '\n';
    }
    return 0;
}
