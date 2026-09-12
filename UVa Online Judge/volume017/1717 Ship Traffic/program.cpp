#include <bits/stdc++.h>
using namespace std;

struct Seg {
    double l, r;
};

bool cmpSeg(const Seg &a, const Seg &b) {
    if (a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, w, u, v, i, j, m, l, p;
    double t1, t2, delta, offset, a, b, cur, ans, left, right;
    char dir;
    while (cin >> n >> w >> u >> v >> t1 >> t2) {
        vector<Seg> segs, merged;
        delta = 1.0 * w / v;
        segs.reserve(100000);
        for (i = 0; i < n; i++) {
            cin >> dir >> m;
            offset = i * delta;
            for (j = 0; j < m; j++) {
                cin >> l >> p;
                if (dir == 'W') {
                    a = 1.0 * p / u - (i + 1) * delta;
                    b = 1.0 * (p + l) / u - i * delta;
                } else {
                    a = -1.0 * p / u - (i + 1) * delta;
                    b = 1.0 * (l - p) / u - i * delta;
                }
                segs.push_back({a, b});
            }
        }
        sort(segs.begin(), segs.end(), cmpSeg);
        for (const Seg &seg : segs) {
            if (merged.empty() || seg.l > merged.back().r) merged.push_back(seg);
            else if (seg.r > merged.back().r) merged.back().r = seg.r;
        }
        cur = t1;
        ans = 0;
        for (const Seg &seg : merged) {
            if (seg.r <= t1) continue;
            if (seg.l >= t2) break;
            left = max(t1, seg.l);
            right = min(t2, seg.r);
            if (left > cur) ans = max(ans, left - cur);
            if (right > cur) cur = right;
        }
        ans = max(ans, t2 - cur);
        cout << fixed << setprecision(8) << ans << '\n';
    }
    return 0;
}
