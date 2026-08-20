#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
    bool operator < (const Point &p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator == (const Point &p) const {
        return x == p.x && y == p.y;
    }
};

ll cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool onSeg(const Point &a, const Point &b, const Point &p) {
    if (cross(a, b, p) != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool segHit(const Point &a, const Point &b, const Point &c, const Point &d) {
    ll c1 = cross(a, b, c), c2 = cross(a, b, d);
    ll c3 = cross(c, d, a), c4 = cross(c, d, b);
    if (c1 == 0 && onSeg(a, b, c)) return true;
    if (c2 == 0 && onSeg(a, b, d)) return true;
    if (c3 == 0 && onSeg(c, d, a)) return true;
    if (c4 == 0 && onSeg(c, d, b)) return true;
    return ((c1 > 0) != (c2 > 0)) && ((c3 > 0) != (c4 > 0));
}

vector<Point> getHull(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    if (p.size() <= 1) return p;
    vector<Point> low, up;
    for (const Point &q : p) {
        while (low.size() >= 2 && cross(low[low.size() - 2], low.back(), q) <= 0) low.pop_back();
        low.push_back(q);
    }
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        while (up.size() >= 2 && cross(up[up.size() - 2], up.back(), p[i]) <= 0) up.pop_back();
        up.push_back(p[i]);
    }
    low.pop_back();
    up.pop_back();
    low.insert(low.end(), up.begin(), up.end());
    return low;
}

bool inHull(const vector<Point> &h, const Point &p) {
    if (h.size() == 1) return h[0] == p;
    if (h.size() == 2) return onSeg(h[0], h[1], p);
    bool pos = false, neg = false;
    for (int i = 0; i < (int)h.size(); i++) {
        ll v = cross(h[i], h[(i + 1) % h.size()], p);
        if (v > 0) pos = true;
        if (v < 0) neg = true;
    }
    return !(pos && neg);
}

bool hullHit(const vector<Point> &a, const vector<Point> &b) {
    int ea = a.size() == 2 ? 1 : (int)a.size(), eb = b.size() == 2 ? 1 : (int)b.size();
    for (int i = 0; i < ea; i++) {
        Point a1 = a[i], a2 = a[(i + 1) % a.size()];
        for (int j = 0; j < eb; j++) {
            Point b1 = b[j], b2 = b[(j + 1) % b.size()];
            if (segHit(a1, a2, b1, b2)) return true;
        }
    }
    for (const Point &p : a)
        if (inHull(b, p)) return true;
    for (const Point &p : b)
        if (inHull(a, p)) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll r;
    while (cin >> n >> r && (n || r)) {
        vector<Point> a, b;
        for (int i = 0; i < n; i++) {
            Point p;
            char t;
            cin >> p.x >> p.y >> t;
            if (t == 'A') a.push_back(p);
            else b.push_back(p);
        }
        vector<Point> ha = getHull(a), hb = getHull(b);
        cout << (hullHit(ha, hb) ? "NOT YET" : "FEED") << '\n';
    }
    return 0;
}
