#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double geo = 1e-8;
const double inf = 1e100;
const double pi = acos(-1.0);

struct Shaft {
    double x, y, r;
    int s;
};

struct EdgeGeom {
    bool ok;
    double ax, ay, bx, by, len;
    EdgeGeom() : ok(false), ax(0), ay(0), bx(0), by(0), len(0) {}
};

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x_, double y_) : x(x_), y(y_) {}
};

struct Segment {
    Point a, b;
};

double distanceToSegment(double px, double py, double ax, double ay, double bx, double by, double &t) {
    double vx = bx - ax, vy = by - ay, wx = px - ax, wy = py - ay;
    double vv = vx * vx + vy * vy;
    t = (wx * vx + wy * vy) / vv;
    double qx = ax + t * vx, qy = ay + t * vy;
    return hypot(px - qx, py - qy);
}

EdgeGeom buildEdge(int a, int b, const vector<Shaft>& shafts, double dmax) {
    EdgeGeom e;
    if (a == b) {
        return e;
    }
    double dx = shafts[b].x - shafts[a].x;
    double dy = shafts[b].y - shafts[a].y;
    double dist2 = dx * dx + dy * dy;
    double delta = shafts[b].s * shafts[b].r - shafts[a].s * shafts[a].r;
    double rem = dist2 - delta * delta;
    if (rem <= EPS) {
        return e;
    }
    double len = sqrt(max(0.0, rem));
    if (!(len + 1e-10 < dmax)) {
        return e;
    }
    double nx = (dx * delta - dy * len) / dist2;
    double ny = (dy * delta + dx * len) / dist2;
    double ax = shafts[a].x - shafts[a].s * shafts[a].r * nx;
    double ay = shafts[a].y - shafts[a].s * shafts[a].r * ny;
    double bx = shafts[b].x - shafts[b].s * shafts[b].r * nx;
    double by = shafts[b].y - shafts[b].s * shafts[b].r * ny;
    for (int c = 0; c < static_cast<int>(shafts.size()); ++c) {
        if (c == a || c == b) {
            continue;
        }
        double tproj;
        double dist = distanceToSegment(shafts[c].x, shafts[c].y, ax, ay, bx, by, tproj);
        if (tproj > EPS && tproj < 1.0 - EPS && dist <= shafts[c].r + 1e-9) {
            return e;
        }
    }
    e.ok = true;
    e.ax = ax;
    e.ay = ay;
    e.bx = bx;
    e.by = by;
    e.len = len;
    return e;
}

double arcLen(int prev, int cur, int nxt, const vector<Shaft>& shafts, const vector<vector<EdgeGeom>>& edge) {
    double inAngle = atan2(edge[prev][cur].by - shafts[cur].y, edge[prev][cur].bx - shafts[cur].x);
    double outAngle = atan2(edge[cur][nxt].ay - shafts[cur].y, edge[cur][nxt].ax - shafts[cur].x);
    double da = shafts[cur].s == 1 ? outAngle - inAngle : inAngle - outAngle;
    if (da < 0.0) {
        da += 2.0 * PI;
    }
    return shafts[cur].r * da;
}

double cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int sgn(double x) {
    if (x > GEO) {
        return 1;
    }
    if (x < -GEO) {
        return -1;
    }
    return 0;
}

bool samePoint(const Point& a, const Point& b) { return hypot(a.x - b.x, a.y - b.y) <= GEO; }

bool onSegment(const Point& a, const Point& b, const Point& p) {
    if (fabs(cross(a, b, p)) > GEO) {
        return false;
    }
    return min(a.x, b.x) - GEO <= p.x && p.x <= max(a.x, b.x) + GEO && min(a.y, b.y) - GEO <= p.y && p.y <= max(a.y, b.y) + GEO;
}

bool segmentsIntersectClosed(const Segment& s1, const Segment& s2) {
    double c1 = cross(s1.a, s1.b, s2.a);
    double c2 = cross(s1.a, s1.b, s2.b);
    double c3 = cross(s2.a, s2.b, s1.a);
    double c4 = cross(s2.a, s2.b, s1.b);
    int s1c = sgn(c1);
    int s2c = sgn(c2);
    int s3c = sgn(c3);
    int s4c = sgn(c4);
    if (s1c * s2c < 0 && s3c * s4c < 0) {
        return true;
    }
    if (s1c == 0 && onSegment(s1.a, s1.b, s2.a)) {
        return true;
    }
    if (s2c == 0 && onSegment(s1.a, s1.b, s2.b)) {
        return true;
    }
    if (s3c == 0 && onSegment(s2.a, s2.b, s1.a)) {
        return true;
    }
    if (s4c == 0 && onSegment(s2.a, s2.b, s1.b)) {
        return true;
    }
    return false;
}

bool badIntersectionWithPrevious(const vector<Segment>& segs, const Segment& nw) {
    for (int i = 0; i < static_cast<int>(segs.size()); ++i) {
        if (!segmentsIntersectClosed(segs[i], nw)) {
            continue;
        }
        bool allowedSharedEndpoint = i == static_cast<int>(segs.size()) - 1 && samePoint(segs[i].b, nw.a);
        if (!allowedSharedEndpoint) {
            return true;
        }
        Point p = segs[i].b;
        if ((onSegment(segs[i].a, segs[i].b, nw.b) && !samePoint(nw.b, p)) || (onSegment(nw.a, nw.b, segs[i].a) && !samePoint(segs[i].a, p))) {
            return true;
        }
    }
    return false;
}

string formatAnswer(double value) {
    double rounded = floor(value * 100.0 + 0.5 + 1e-9) / 100.0;
    ostringstream out;
    out << fixed << setprecision(2) << rounded;
    string s = out.str();
    while (!s.empty() && s.back() == '0') {
        s.pop_back();
    }
    if (!s.empty() && s.back() == '.') {
        s.pop_back();
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int tc = 1;
    while (cin >> n && n != 0) {
        vector<Shaft> shafts(n);
        for (int i = 0; i < n; ++i) {
            string rot;
            cin >> shafts[i].x >> shafts[i].y >> shafts[i].r >> rot;
            shafts[i].s = rot == "CC" ? 1 : -1;
        }
        int start, finish;
        double dmax;
        cin >> start >> finish >> dmax;
        double best = INF;
        vector<vector<EdgeGeom>> edge(n, vector<EdgeGeom>(n));
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                edge[a][b] = buildEdge(a, b, shafts, dmax);
            }
        }
        if (edge[start][finish].ok) {
            best = min(best, edge[start][finish].len);
        }
        auto stateId = [&](int prev, int cur) { return (prev + 1) * n + cur; };
        vector<double> lb((n + 1) * n, INF);
        vector<vector<pair<int, double>>> rev((n + 1) * n);
        for (int prev = -1; prev < n; ++prev) {
            for (int cur = 0; cur < n; ++cur) {
                if (prev == cur) {
                    continue;
                }
                int sid = stateId(prev, cur);
                for (int nxt = 0; nxt < n; ++nxt) {
                    if (nxt == cur || !edge[cur][nxt].ok) {
                        continue;
                    }
                    double w = edge[cur][nxt].len;
                    if (prev != -1) {
                        w += arcLen(prev, cur, nxt, shafts, edge);
                    }
                    rev[stateId(cur, nxt)].emplace_back(sid, w);
                }
            }
        }
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        for (int prev = -1; prev < n; ++prev) {
            if (prev == finish) {
                continue;
            }
            int sid = stateId(prev, finish);
            lb[sid] = 0.0;
            pq.emplace(0.0, sid);
        }
        while (!pq.empty()) {
            double cd = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (cd > lb[u] + 1e-12) {
                continue;
            }
            for (const auto& e : rev[u]) {
                int v = e.first;
                double nd = cd + e.second;
                if (nd + 1e-12 < lb[v]) {
                    lb[v] = nd;
                    pq.emplace(nd, v);
                }
            }
        }
        vector<int> used(n, 0);
        vector<Segment> segs;
        used[start] = 1;
        function<void(int, int, double)> dfs = [&](int prev, int cur, double cost) {
            int sid = stateId(prev, cur);
            if (cost + lb[sid] >= best - 1e-12) {
                return;
            }
            if (cur == finish) {
                best = min(best, cost);
                return;
            }
            for (int nxt = 0; nxt < n; ++nxt) {
                if (used[nxt] || !edge[cur][nxt].ok) {
                    continue;
                }
                double add = edge[cur][nxt].len;
                if (prev != -1) {
                    add += arcLen(prev, cur, nxt, shafts, edge);
                }
                if (cost + add + lb[stateId(cur, nxt)] >= best - 1e-12) {
                    continue;
                }
                Segment nw{Point(edge[cur][nxt].ax, edge[cur][nxt].ay), Point(edge[cur][nxt].bx, edge[cur][nxt].by)};
                if (badIntersectionWithPrevious(segs, nw)) {
                    continue;
                }
                used[nxt] = 1;
                segs.push_back(nw);
                dfs(cur, nxt, cost + add);
                segs.pop_back();
                used[nxt] = 0;
            }
        };
        dfs(-1, start, 0.0);
        if (best >= INF / 2.0) {
            cout << "Case " << tc++ << ": Cannot reach destination shaft\n";
        } else {
            cout << "Case " << tc++ << ": length = " << formatAnswer(best) << '\n';
        }
    }
    return 0;
}
