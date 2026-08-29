#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;

struct Pt { double x, y; };
bool operator<(const Pt& a, const Pt& b) { if (fabs(a.x - b.x) > EPS) return a.x < b.x; return a.y < b.y; }
bool operator==(const Pt& a, const Pt& b) { return fabs(a.x - b.x) < EPS && fabs(a.y - b.y) < EPS; }
struct Seg { Pt a, b; };

double cross(const Pt& a, const Pt& b, const Pt& c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
double dot(const Pt& a, const Pt& b) { return a.x * b.x + a.y * b.y; }
double dist2(const Pt& a, const Pt& b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
double dist(const Pt& a, const Pt& b) { return sqrt(dist2(a, b)); }

bool onSeg(const Pt& p, const Pt& a, const Pt& b) {
    if (fabs(cross(a, b, p)) > EPS) return false;
    return dot({p.x - a.x, p.y - a.y}, {p.x - b.x, p.y - b.y}) <= EPS;
}

double distPointSeg(const Pt& p, const Seg& s) {
    Pt a = s.a, b = s.b, v = {b.x - a.x, b.y - a.y}, w = {p.x - a.x, p.y - a.y};
    double c1 = dot(w, v);
    if (c1 <= 0) return dist(p, a);
    double c2 = dot({p.x - b.x, p.y - b.y}, {a.x - b.x, a.y - b.y});
    if (c2 <= 0) return dist(p, b);
    double t = c1 / dist2(a, b);
    Pt proj = {a.x + t * v.x, a.y + t * v.y};
    return dist(p, proj);
}

void getIntersections(const Seg& s1, const Seg& s2, vector<Pt>& out) {
    Pt a = s1.a, b = s1.b, c = s2.a, d = s2.b;
    double ux = b.x - a.x, uy = b.y - a.y, vx = d.x - c.x, vy = d.y - c.y;
    double denom = ux * vy - uy * vx;
    if (fabs(denom) < EPS) {
        if (fabs(cross(a, b, c)) > EPS) return;
        double len2 = ux * ux + uy * uy;
        if (len2 < EPS) return;
        double tc = ((c.x - a.x) * ux + (c.y - a.y) * uy) / len2;
        double td = ((d.x - a.x) * ux + (d.y - a.y) * uy) / len2;
        double L = max(0.0, min(tc, td)), R = min(1.0, max(tc, td));
        if (L <= R + EPS) {
            out.push_back({a.x + L * ux, a.y + L * uy});
            out.push_back({a.x + R * ux, a.y + R * uy});
        }
        return;
    }
    double t = ((c.x - a.x) * vy - (c.y - a.y) * vx) / denom;
    double s = ((c.x - a.x) * uy - (c.y - a.y) * ux) / denom;
    if (t >= -EPS && t <= 1 + EPS && s >= -EPS && s <= 1 + EPS)
        out.push_back({a.x + t * ux, a.y + t * uy});
}

void normalize(vector<Seg>& segs) {
    vector<Pt> pts;
    for (auto& s : segs) { pts.push_back(s.a); pts.push_back(s.b); }
    int m = segs.size();
    for (int i = 0; i < m; i++) for (int j = i + 1; j < m; j++) getIntersections(segs[i], segs[j], pts);
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    set<pair<int,int>> edges;
    for (auto& s : segs) {
        Pt a = s.a, b = s.b;
        double len2 = dist2(a, b);
        if (len2 < EPS) continue;
        vector<int> idxs;
        for (int i = 0; i < (int)pts.size(); i++) if (onSeg(pts[i], a, b)) idxs.push_back(i);
        sort(idxs.begin(), idxs.end(), [&](int i, int j) {
            double ti = ((pts[i].x - a.x) * (b.x - a.x) + (pts[i].y - a.y) * (b.y - a.y)) / len2;
            double tj = ((pts[j].x - a.x) * (b.x - a.x) + (pts[j].y - a.y) * (b.y - a.y)) / len2;
            return ti < tj;
        });
        idxs.erase(unique(idxs.begin(), idxs.end()), idxs.end());
        for (int k = 0; k + 1 < (int)idxs.size(); k++) {
            int u = idxs[k], v = idxs[k + 1];
            if (u == v) continue;
            if (u > v) swap(u, v);
            edges.insert({u, v});
        }
    }
    bool changed = true;
    while (changed) {
        changed = false;
        int V = pts.size();
        vector<vector<int>> adj(V);
        for (auto& e : edges) { adj[e.first].push_back(e.second); adj[e.second].push_back(e.first); }
        for (int i = 0; i < V; i++) if (adj[i].size() == 2) {
            int u = adj[i][0], v = adj[i][1];
            if (fabs(cross(pts[u], pts[i], pts[v])) < EPS &&
                dot({pts[u].x - pts[i].x, pts[u].y - pts[i].y}, {pts[v].x - pts[i].x, pts[v].y - pts[i].y}) < -EPS) {
                int a = u, b = v; if (a > b) swap(a, b);
                edges.erase({min(u, i), max(u, i)});
                edges.erase({min(i, v), max(i, v)});
                edges.insert({a, b});
                changed = true;
                break;
            }
        }
    }
    vector<int> used;
    for (auto& e : edges) { used.push_back(e.first); used.push_back(e.second); }
    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());
    vector<Pt> newPts;
    for (int idx : used) newPts.push_back(pts[idx]);
    sort(newPts.begin(), newPts.end());
    map<int,int> mp;
    for (int i = 0; i < (int)newPts.size(); i++) for (int j = 0; j < (int)pts.size(); j++)
        if (pts[j] == newPts[i]) { mp[j] = i; break; }
    set<pair<int,int>> newEdges;
    for (auto& e : edges) {
        int u = mp[e.first], v = mp[e.second];
        if (u > v) swap(u, v);
        newEdges.insert({u, v});
    }
    segs.clear();
    for (auto& e : newEdges) segs.push_back({newPts[e.first], newPts[e.second]});
}

void output(const vector<Seg>& segs) {
    vector<Pt> pts;
    for (auto& s : segs) { pts.push_back(s.a); pts.push_back(s.b); }
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    set<pair<int,int>> edges;
    for (auto& s : segs) {
        int u = -1, v = -1;
        for (int i = 0; i < (int)pts.size(); i++) {
            if (pts[i] == s.a) u = i;
            if (pts[i] == s.b) v = i;
        }
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }
    int V = pts.size(), E = edges.size();
    printf("%d\n", V);
    for (auto& p : pts) {
        double x = p.x + 1e-6, y = p.y + 1e-6;
        if (fabs(x) < 5e-7) x = 0;
        if (fabs(y) < 5e-7) y = 0;
        printf("%.2f %.2f\n", x, y);
    }
    printf("%d\n", E);
    for (auto& e : edges) printf("%d %d\n", e.first + 1, e.second + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n && n) {
        cin.ignore();
        vector<Seg> segs;
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);
            stringstream ss(line);
            string op;
            ss >> op;
            if (op == "DRAW") {
                vector<Pt> pts;
                double x, y;
                while (ss >> x >> y) pts.push_back({x, y});
                for (int j = 0; j + 1 < (int)pts.size(); j++)
                    if (dist2(pts[j], pts[j + 1]) > EPS) segs.push_back({pts[j], pts[j + 1]});
                normalize(segs);
            } else if (op == "REMOVE") {
                double x, y, d;
                ss >> x >> y >> d;
                vector<bool> del(segs.size(), false);
                for (int j = 0; j < (int)segs.size(); j++)
                    if (distPointSeg({x, y}, segs[j]) <= d + EPS) del[j] = true;
                vector<Seg> newSegs;
                for (int j = 0; j < (int)segs.size(); j++) if (!del[j]) newSegs.push_back(segs[j]);
                segs.swap(newSegs);
                normalize(segs);
            }
        }
        string end;
        cin >> end;
        output(segs);
    }
    return 0;
}
