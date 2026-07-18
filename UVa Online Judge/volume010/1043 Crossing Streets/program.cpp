// Crossing Streets
// UVa ID: 1043
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct Point {
    ll x, y;
    bool operator<(const Point& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
};

struct Seg {
    ll x1, y1, x2, y2;
    bool hor;
    void normalize() {
        if (hor) { if (x1 > x2) swap(x1, x2); }
        else     { if (y1 > y2) swap(y1, y2); }
    }
};

vector<Seg> mergeSegs(const vector<Seg>& segs) {
    vector<Seg> hor, ver, res;
    for (auto& s : segs) {
        if (s.hor) hor.push_back(s);
        else ver.push_back(s);
    }
    map<ll, vector<pair<ll,ll>>> mpH;
    for (auto& s : hor) mpH[s.y1].push_back({s.x1, s.x2});
    for (auto& kv : mpH) {
        ll y = kv.first;
        auto& v = kv.second;
        sort(v.begin(), v.end());
        ll l = v[0].first, r = v[0].second;
        for (int i = 1; i < (int)v.size(); ++i) {
            if (v[i].first <= r) r = max(r, v[i].second);
            else { res.push_back({l, y, r, y, true}); l = v[i].first; r = v[i].second; }
        }
        res.push_back({l, y, r, y, true});
    }
    map<ll, vector<pair<ll,ll>>> mpV;
    for (auto& s : ver) mpV[s.x1].push_back({s.y1, s.y2});
    for (auto& kv : mpV) {
        ll x = kv.first;
        auto& v = kv.second;
        sort(v.begin(), v.end());
        ll l = v[0].first, r = v[0].second;
        for (int i = 1; i < (int)v.size(); ++i) {
            if (v[i].first <= r) r = max(r, v[i].second);
            else { res.push_back({x, l, x, r, false}); l = v[i].first; r = v[i].second; }
        }
        res.push_back({x, l, x, r, false});
    }
    return res;
}

bool onSegment(Point p, Point a, Point b) {
    ll cross = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    if (cross != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

int intersectLineSeg(Point a, Point b, const Seg& s, long double& ix, long double& iy) {
    if (s.hor) {
        ll y = s.y1;
        if ((a.y < y && b.y < y) || (a.y > y && b.y > y)) return 0;
        if (a.y == y && b.y == y) {
            ll l = max(min(a.x, b.x), s.x1);
            ll r = min(max(a.x, b.x), s.x2);
            if (l < r) return -1;
            return 0;
        }
        long double t = (long double)(y - a.y) / (b.y - a.y);
        if (t < 0 || t > 1) return 0;
        long double x = a.x + t * (b.x - a.x);
        if (x < s.x1 - 1e-9 || x > s.x2 + 1e-9) return 0;
        ix = x; iy = y;
        if (fabsl(x - s.x1) < 1e-9 || fabsl(x - s.x2) < 1e-9) return 2;
        return 1;
    }
    else {
        ll x = s.x1;
        if ((a.x < x && b.x < x) || (a.x > x && b.x > x)) return 0;
        if (a.x == x && b.x == x) {
            ll l = max(min(a.y, b.y), s.y1);
            ll r = min(max(a.y, b.y), s.y2);
            if (l < r) return -1;
            return 0;
        }
        long double t = (long double)(x - a.x) / (b.x - a.x);
        if (t < 0 || t > 1) return 0;
        long double y = a.y + t * (b.y - a.y);
        if (y < s.y1 - 1e-9 || y > s.y2 + 1e-9) return 0;
        ix = x; iy = y;
        if (fabsl(y - s.y1) < 1e-9 || fabsl(y - s.y2) < 1e-9) return 2;
        return 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNo = 0;
    while (true) {
        int n; cin >> n;
        if (n == 0) break;
        ++caseNo;
        vector<Seg> inputSegs;
        for (int i = 0; i < n; ++i) {
            Seg s;
            cin >> s.x1 >> s.y1 >> s.x2 >> s.y2;
            s.hor = (s.y1 == s.y2);
            s.normalize();
            inputSegs.push_back(s);
        }
        Point home, uni;
        cin >> home.x >> home.y >> uni.x >> uni.y;
        vector<Seg> segs = mergeSegs(inputSegs);
        int m = segs.size();
        set<pair<ll,ll>> interPts;
        for (int i = 0; i < m; ++i) if (segs[i].hor) {
            for (int j = 0; j < m; ++j) if (!segs[j].hor) {
                ll x = segs[j].x1, y = segs[i].y1;
                if (segs[i].x1 <= x && x <= segs[i].x2 &&
                    segs[j].y1 <= y && y <= segs[j].y2) {
                    interPts.insert({x, y});
                }
            }
        }
        set<Point> nodeSet;
        for (auto& s : segs) {
            nodeSet.insert({s.x1, s.y1});
            nodeSet.insert({s.x2, s.y2});
        }
        nodeSet.insert(home);
        nodeSet.insert(uni);
        vector<Point> nodes(nodeSet.begin(), nodeSet.end());
        int V = nodes.size();
        int sIdx = -1, tIdx = -1;
        for (int i = 0; i < V; ++i) {
            if (nodes[i] == home) sIdx = i;
            if (nodes[i] == uni) tIdx = i;
        }
        vector<ll> dist(V, INF);
        vector<bool> vis(V, false);
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        dist[sIdx] = 0;
        pq.push({0, sIdx});
        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            ll d = cur.first; int u = cur.second;
            if (vis[u]) continue;
            vis[u] = true;
            if (u == tIdx) break;
            for (int v = 0; v < V; ++v) if (u != v) {
                Point a = nodes[u], b = nodes[v];
                bool bad = false;
                int cost = 0;
                for (auto& seg : segs) {
                    long double ix, iy;
                    int ret = intersectLineSeg(a, b, seg, ix, iy);
                    if (ret == -1) { bad = true; break; }
                    if (ret == 0) continue;
                    ll rx = llround(ix), ry = llround(iy);
                    if (fabsl(ix - rx) < 1e-9 && fabsl(iy - ry) < 1e-9) {
                        if (interPts.count({rx, ry})) { bad = true; break; }
                    }
                    if (ret == 1) ++cost;
                }
                if (bad) continue;
                if (dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    pq.push({dist[v], v});
                }
            }
        }
        cout << "City " << caseNo << " Peter has to cross " << dist[tIdx] << " streets\n";
    }
    return 0;
}
