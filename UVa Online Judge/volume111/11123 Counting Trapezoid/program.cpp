// Counting Trapezoid
// UVa ID: 11123
// Verdict: Accepted
// Submission Date: 2026-05-30
// UVa Run Time: 0.170s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<int, int> normDir(int dx, int dy) {
    if (dx == 0 && dy == 0) return {0, 0};
    int g = __gcd(abs(dx), abs(dy));
    dx /= g; dy /= g;
    if (dx < 0 || (dx == 0 && dy < 0)) { dx = -dx; dy = -dy; }
    return {dx, dy};
}

struct Line {
    ll a, b, c;
    Line(ll a_, ll b_, ll c_) : a(a_), b(b_), c(c_) {
        ll g = __gcd(__gcd(abs(a), abs(b)), abs(c));
        if (g) { a /= g; b /= g; c /= g; }
        if (a < 0 || (a == 0 && b < 0)) { a = -a; b = -b; c = -c; }
    }
    bool operator<(const Line& o) const {
        if (a != o.a) return a < o.a;
        if (b != o.b) return b < o.b;
        return c < o.c;
    }
};

struct Segment {
    int i, j;
    ll len2;
    pair<int, int> dir;
    Segment(int i_, int j_, ll len2_, pair<int, int> dir_)
        : i(i_), j(j_), len2(len2_), dir(dir_) {}
    bool operator<(const Segment& o) const {
        if (dir != o.dir) return dir < o.dir;
        return len2 < o.len2;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, caseNo = 0;
    while (cin >> n, n) {
        vector<pair<ll, ll>> pts(n);
        for (int i = 0; i < n; ++i)
            cin >> pts[i].first >> pts[i].second;

        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        n = pts.size();

        if (n < 4) {
            cout << "Case " << ++caseNo << ": 0\n";
            continue;
        }

        // Step 1: count all quads with at least one pair of parallel sides
        map<pair<int, int>, map<Line, set<int>>> dirLines;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                ll dx = pts[j].first - pts[i].first;
                ll dy = pts[j].second - pts[i].second;
                auto dir = normDir(dx, dy);
                ll a = dy, b = -dx;
                ll c = a * pts[i].first + b * pts[i].second;
                Line line(a, b, c);
                dirLines[dir][line].insert(i);
                dirLines[dir][line].insert(j);
            }

        ll totalParallel = 0;
        for (auto& de : dirLines) {
            vector<int> cnts;
            for (auto& li : de.second)
                cnts.push_back(li.second.size());
            int m = cnts.size();
            for (int i = 0; i < m; ++i)
                for (int j = i + 1; j < m; ++j)
                    totalParallel += (ll)cnts[i] * (cnts[i] - 1) / 2 * cnts[j] * (cnts[j] - 1) / 2;
        }

        // Step 2: count parallelograms via same direction & same length
        vector<Segment> segs;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                ll dx = pts[j].first - pts[i].first;
                ll dy = pts[j].second - pts[i].second;
                ll len2 = dx * dx + dy * dy;
                auto dir = normDir(dx, dy);
                segs.emplace_back(i, j, len2, dir);
            }

        sort(segs.begin(), segs.end());

        ll totalPara = 0;
        int sz = segs.size();
        for (int i = 0; i < sz; ++i) {
            int j = i;
            while (j < sz && segs[j].dir == segs[i].dir && segs[j].len2 == segs[i].len2)
                ++j;
            int cnt = j - i;
            if (cnt >= 2) {
                for (int p = i; p < j; ++p)
                    for (int q = p + 1; q < j; ++q) {
                        int a = segs[p].i, b = segs[p].j;
                        int c = segs[q].i, d = segs[q].j;
                        set<int> quad = {a, b, c, d};
                        if (quad.size() != 4) continue;
                        ll area = (pts[b].first - pts[a].first) * (pts[c].second - pts[a].second)
                                - (pts[b].second - pts[a].second) * (pts[c].first - pts[a].first);
                        if (area != 0) ++totalPara;
                    }
            }
            i = j - 1;
        }

        // Each parallelogram is counted twice in totalParallel and twice in totalPara
        cout << "Case " << ++caseNo << ": " << totalParallel - totalPara << "\n";
    }

    return 0;
}
