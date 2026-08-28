#include <bits/stdc++.h>
using namespace std;

using ld = long double;

struct Seg {
    ld xa, ya, xb, yb;
};

ld getDist(const Seg &s, ld x) {
    ld vx = s.xb - s.xa, vy = s.yb - s.ya, wx = x - s.xa, wy = -s.ya;
    ld len = vx * vx + vy * vy, t;
    if (len == 0) return hypotl(wx, wy);
    t = (wx * vx + wy * vy) / len;
    t = max((ld)0, min((ld)1, t));
    return hypotl(x - s.xa - t * vx, -s.ya - t * vy);
}

ld getMinX(const Seg &s) {
    if (s.ya == s.yb) return (s.xa + s.xb) / 2;
    if (s.ya * s.yb <= 0) return s.xa + (s.xb - s.xa) * (-s.ya) / (s.yb - s.ya);
    if (fabsl(s.ya) < fabsl(s.yb)) return s.xa;
    return s.xb;
}

bool check(const vector<Seg> &segs, ld lmt, ld r) {
    vector<pair<ld, ld>> ints;
    for (const Seg &s : segs) {
        ld x0 = getMinX(s), xm = max((ld)0, min(lmt, x0));
        if (getDist(s, xm) > r) continue;
        ld le = 0, ri = xm;
        if (getDist(s, 0) <= r) le = 0;
        else {
            for (int k = 0; k < 70; k++) {
                ld md = (le + ri) / 2;
                if (getDist(s, md) <= r) ri = md;
                else le = md;
            }
            le = ri;
        }
        le = 0;
        if (getDist(s, 0) > r) {
            ld a = 0, b = xm;
            for (int k = 0; k < 70; k++) {
                ld md = (a + b) / 2;
                if (getDist(s, md) <= r) b = md;
                else a = md;
            }
            le = b;
        }
        ri = lmt;
        if (getDist(s, lmt) > r) {
            ld a = xm, b = lmt;
            for (int k = 0; k < 70; k++) {
                ld md = (a + b) / 2;
                if (getDist(s, md) <= r) a = md;
                else b = md;
            }
            ri = a;
        }
        ints.push_back({le, ri});
    }
    sort(ints.begin(), ints.end());
    ld cur = 0;
    for (const pair<ld, ld> &p : ints) {
        if (p.first > cur + 1e-12L) return true;
        cur = max(cur, p.second);
        if (cur >= lmt - 1e-12L) return false;
    }
    return cur < lmt - 1e-12L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    cout << fixed << setprecision(3);
    while (tc--) {
        int n;
        ld lmt;
        cin >> n >> lmt;
        vector<Seg> segs(n);
        for (Seg &s : segs) cin >> s.xa >> s.ya >> s.xb >> s.yb;
        ld lo = 0, hi = 100000;
        for (int k = 0; k < 80; k++) {
            ld md = (lo + hi) / 2;
            if (check(segs, lmt, md)) lo = md;
            else hi = md;
        }
        cout << (double)lo << '\n';
    }
    return 0;
}
