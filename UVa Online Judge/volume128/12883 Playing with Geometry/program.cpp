#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    bool operator == (const Point &other) const {
        return x == other.x && y == other.y;
    }
};

vector<Point> canonical(vector<Point> p) {
    int n = p.size(), st = 0;
    for (int i = 0; i < n; i++)
        if (p[i].y == 0 && p[(i + 1) % n].y == 0 && p[i].x < p[(i + 1) % n].x) {
            st = i;
            break;
        }
    vector<Point> res;
    for (int i = 0; i < n; i++) res.push_back(p[(st + i) % n]);
    return res;
}

vector<Point> normalize(vector<Point> p) {
    vector<int> xs, ys;
    for (const Point &q : p) {
        xs.push_back(q.x);
        ys.push_back(q.y);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (Point &q : p) {
        q.x = lower_bound(xs.begin(), xs.end(), q.x) - xs.begin();
        q.y = lower_bound(ys.begin(), ys.end(), q.y) - ys.begin();
    }
    return canonical(p);
}

vector<Point> turnShape(vector<Point> p) {
    int side = 0;
    for (const Point &q : p) side = max(side, max(q.x, q.y));
    for (Point &q : p) {
        int x = q.x, y = q.y;
        q.x = y;
        q.y = side - x;
    }
    return canonical(p);
}

vector<Point> readPolygon(int n) {
    vector<Point> p(n);
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    return normalize(p);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n) {
        vector<Point> a, b;
        a = readPolygon(n);
        if (!(cin >> m)) break;
        b = readPolygon(m);
        bool ok = false;
        for (int i = 0; i < 4; i++) {
            if (a == b) ok = true;
            b = turnShape(b);
        }
        cout << (ok ? "yes" : "no") << '\n';
    }
    return 0;
}
