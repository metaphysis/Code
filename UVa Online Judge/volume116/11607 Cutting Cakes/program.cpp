#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Event {
    int a, b, num, den;
};

struct Query {
    int id, x, y, dx, dy, num, den;
};

struct Answer {
    int p, q, r;
};

bool eventCmp(const Event &a, const Event &b) {
    return 1LL * a.num * b.den < 1LL * b.num * a.den;
}

bool queryCmp(const Query &a, const Query &b) {
    return 1LL * a.num * b.den < 1LL * b.num * a.den;
}

int modVal(long long x) {
    x %= 10000;
    if (x < 0) x += 10000;
    return (int)x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n;
        cin >> n;
        vector<Point> pts(n);
        for (int i = 0; i < n; i++)
            cin >> pts[i].x >> pts[i].y;
        int m, x1, y1, x2, y2, dx1, dy1, dx2, dy2;
        cin >> m >> x1 >> y1 >> x2 >> y2 >> dx1 >> dy1 >> dx2 >> dy2;
        vector<Event> events;
        events.reserve(1LL * n * (n - 1) / 2);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int num = pts[j].y - pts[i].y, den = pts[j].x - pts[i].x;
                if (den < 0) {
                    den = -den;
                    num = -num;
                }
                if (den != 0) events.push_back({i, j, num, den});
            }
        }
        sort(events.begin(), events.end(), eventCmp);
        vector<int> xs;
        xs.reserve(n);
        for (int i = 0; i < n; i++)
            xs.push_back(pts[i].x);
        sort(xs.begin(), xs.end());
        vector<Query> queries;
        vector<Answer> ans(m);
        queries.reserve(m);
        for (int i = 0; i < m; i++) {
            x1 = modVal(1LL * x1 + dx1);
            y1 = modVal(1LL * y1 + dy1);
            x2 = modVal(1LL * x2 + dx2);
            y2 = modVal(1LL * y2 + dy2);
            if (x1 == x2 && y1 == y2) y2 = (y1 + 1) % 10000;
            if (x1 == x2) {
                int l = lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
                int r = upper_bound(xs.begin(), xs.end(), x1) - xs.begin();
                int a = l, b = n - r;
                ans[i] = {min(a, b), max(a, b), r - l};
            } else {
                int dx = x2 - x1, dy = y2 - y1;
                if (dx < 0) {
                    dx = -dx;
                    dy = -dy;
                }
                queries.push_back({i, x1, y1, dx, dy, dy, dx});
            }
        }
        sort(queries.begin(), queries.end(), queryCmp);
        vector<int> ord(n), pos(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            if (pts[a].x != pts[b].x) return pts[a].x < pts[b].x;
            return pts[a].y < pts[b].y;
        });
        for (int i = 0; i < n; i++)
            pos[ord[i]] = i;
        int ei = 0;
        for (const Query &q : queries) {
            while (ei < (int)events.size() && 1LL * events[ei].num * q.den < 1LL * q.num * events[ei].den) {
                int a = events[ei].a, b = events[ei].b;
                int pa = pos[a], pb = pos[b];
                swap(ord[pa], ord[pb]);
                swap(pos[a], pos[b]);
                ei++;
            }
            long long base = 1LL * q.y * q.dx - 1LL * q.dy * q.x;
            int l = 0, r = n;
            while (l < r) {
                int mid = (l + r) >> 1;
                Point p = pts[ord[mid]];
                long long val = 1LL * p.y * q.dx - 1LL * q.dy * p.x;
                if (val < base) l = mid + 1;
                else r = mid;
            }
            int left = l;
            l = 0;
            r = n;
            while (l < r) {
                int mid = (l + r) >> 1;
                Point p = pts[ord[mid]];
                long long val = 1LL * p.y * q.dx - 1LL * q.dy * p.x;
                if (val <= base) l = mid + 1;
                else r = mid;
            }
            int right = l, a = left, b = n - right;
            ans[q.id] = {min(a, b), max(a, b), right - left};
        }
        cout << "Case #" << tc << ":\n";
        for (int i = 0; i < m; i++)
            cout << ans[i].p << ' ' << ans[i].q << ' ' << ans[i].r << '\n';
    }
    return 0;
}
