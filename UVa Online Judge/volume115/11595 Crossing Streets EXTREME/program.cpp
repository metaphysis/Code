#include <bits/stdc++.h>
using namespace std;

using I128 = __int128_t;

struct Rat {
    I128 n, d;
    Rat(I128 nn = 0, I128 dd = 1) {
        n = nn;
        d = dd;
        norm();
    }
    void norm() {
        if (d < 0) {
            n = -n;
            d = -d;
        }
        I128 a = n < 0 ? -n : n, b = d, t;
        while (b != 0) {
            t = a % b;
            a = b;
            b = t;
        }
        if (a != 0) {
            n /= a;
            d /= a;
        }
    }
};

struct Point {
    Rat x, y;
};

struct Line {
    long long a, b, c;
};

struct Crowd {
    long long x, y, w;
};

struct Query {
    long long hx, hy, ux, uy;
};

struct Edge {
    int u, v;
    long long w;
};

I128 cmpRat(const Rat &a, const Rat &b) {
    return a.n * b.d - b.n * a.d;
}

bool sameRat(const Rat &a, const Rat &b) {
    return a.n * b.d == b.n * a.d;
}

bool samePoint(const Point &a, const Point &b) {
    return sameRat(a.x, b.x) && sameRat(a.y, b.y);
}

Rat addRat(const Rat &a, const Rat &b) {
    return Rat(a.n * b.d + b.n * a.d, a.d * b.d);
}

Rat addInt(const Rat &a, I128 v) {
    return Rat(a.n + v * a.d, a.d);
}

Rat getParam(const Point &p, const Line &l) {
    return Rat(p.x.n * l.b * p.y.d - p.y.n * l.a * p.x.d, p.x.d * p.y.d);
}

Point getCross(const Line &u, const Line &v) {
    I128 det = (I128)u.a * v.b - (I128)v.a * u.b;
    I128 xn = (I128)u.b * v.c - (I128)v.b * u.c;
    I128 yn = (I128)u.c * v.a - (I128)v.c * u.a;
    return {Rat(xn, det), Rat(yn, det)};
}

I128 evalLine(const Line &l, const Point &p) {
    return (I128)l.a * p.x.n * p.y.d + (I128)l.b * p.y.n * p.x.d + (I128)l.c * p.x.d * p.y.d;
}

string getSign(const Point &p, const vector<Line> &lines) {
    string s;
    for (const Line &l : lines)
        s += evalLine(l, p) > 0 ? '+' : '-';
    return s;
}

int getId(const string &s, map<string, int> &id, vector<string> &names) {
    auto it = id.find(s);
    if (it != id.end())
        return it->second;
    int v = names.size();
    id[s] = v;
    names.push_back(s);
    return v;
}

Point getSegmentPoint(const vector<Point> &points, int pos, const Line &l) {
    int m = points.size();
    if (pos == 0)
        return {addInt(points[0].x, -(I128)l.b), addInt(points[0].y, (I128)l.a)};
    if (pos == m)
        return {addInt(points[m - 1].x, (I128)l.b), addInt(points[m - 1].y, -(I128)l.a)};
    return {Rat(points[pos - 1].x.n * points[pos].x.d + points[pos].x.n * points[pos - 1].x.d, 2 * points[pos - 1].x.d * points[pos].x.d), Rat(points[pos - 1].y.n * points[pos].y.d + points[pos].y.n * points[pos - 1].y.d, 2 * points[pos - 1].y.d * points[pos].y.d)};
}

string getSideSign(const Point &p, const vector<Line> &lines, int skip, int side) {
    string s;
    for (int i = 0; i < (int)lines.size(); i++) {
        if (i == skip)
            s += side > 0 ? '+' : '-';
        else
            s += evalLine(lines[i], p) > 0 ? '+' : '-';
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, c, q, tc = 0;
    while (cin >> n >> c >> q && (n || c || q)) {
        vector<Line> lines(n);
        vector<Crowd> crowds(c);
        vector<Query> queries(q);
        for (Line &l : lines)
            cin >> l.a >> l.b >> l.c;
        for (Crowd &p : crowds)
            cin >> p.x >> p.y >> p.w;
        for (Query &ask : queries)
            cin >> ask.hx >> ask.hy >> ask.ux >> ask.uy;
        map<string, int> id;
        vector<string> names;
        vector<pair<int, int>> rawEdges;
        for (int i = 0; i < n; i++) {
            vector<Point> points;
            for (int j = 0; j < n; j++)
                if (i != j)
                    points.push_back(getCross(lines[i], lines[j]));
            sort(points.begin(), points.end(), [&](const Point &u, const Point &v) {
                return cmpRat(getParam(u, lines[i]), getParam(v, lines[i])) < 0;
            });
            vector<Point> uniq;
            for (const Point &p : points)
                if (uniq.empty() || !samePoint(uniq.back(), p))
                    uniq.push_back(p);
            for (int j = 0; j <= (int)uniq.size(); j++) {
                Point p = getSegmentPoint(uniq, j, lines[i]);
                string left = getSideSign(p, lines, i, -1);
                string right = getSideSign(p, lines, i, 1);
                int u = getId(left, id, names), v = getId(right, id, names);
                rawEdges.push_back({u, v});
            }
        }
        vector<long long> cost(names.size(), 0);
        for (const Crowd &p : crowds) {
            Point cp = {Rat(p.x), Rat(p.y)};
            string s = getSign(cp, lines);
            int v = getId(s, id, names);
            if (v >= (int)cost.size())
                cost.resize(names.size(), 0);
            cost[v] += p.w;
        }
        vector<Edge> edges;
        vector<vector<pair<int, long long>>> graph(names.size());
        for (const auto &e : rawEdges) {
            long long w = 1 + cost[e.first] + cost[e.second];
            edges.push_back({e.first, e.second, w});
            graph[e.first].push_back({e.second, w});
            graph[e.second].push_back({e.first, w});
        }
        cout << "Case " << ++tc << ":\n";
        for (const Query &ask : queries) {
            Point hp = {Rat(ask.hx), Rat(ask.hy)}, up = {Rat(ask.ux), Rat(ask.uy)};
            int st = getId(getSign(hp, lines), id, names), ed = getId(getSign(up, lines), id, names);
            while ((int)graph.size() < (int)names.size())
                graph.push_back({});
            const long long inf = LLONG_MAX / 4;
            vector<long long> dis(names.size(), inf);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            dis[st] = 0;
            pq.push({0, st});
            while (!pq.empty()) {
                auto cur = pq.top();
                pq.pop();
                long long d = cur.first;
                int u = cur.second;
                if (d != dis[u])
                    continue;
                if (u == ed)
                    break;
                for (const auto &to : graph[u]) {
                    int v = to.first;
                    long long nd = d + to.second;
                    if (nd < dis[v]) {
                        dis[v] = nd;
                        pq.push({nd, v});
                    }
                }
            }
            cout << dis[ed] << '\n';
        }
    }
    return 0;
}
