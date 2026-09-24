// Adding New Machine
// UVa ID: 1492
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.480s

#include <bits/stdc++.h>
using namespace std;

struct Rect { long long x1, y1, x2, y2; };

class SegTree {
public:
    int n;
    vector<long long> xs;
    vector<int> cover;
    vector<long long> coveredLen;

    SegTree(int n_, const vector<long long>& xs_) : n(n_), xs(xs_) {
        cover.assign(4 * n + 5, 0);
        coveredLen.assign(4 * n + 5, 0);
    }

    void pushUp(int idx, int l, int r) {
        if (cover[idx] > 0) {
            coveredLen[idx] = xs[r + 1] - xs[l];
        } else if (l == r) {
            coveredLen[idx] = 0;
        } else {
            coveredLen[idx] = coveredLen[idx << 1] + coveredLen[idx << 1 | 1];
        }
    }

    void update(int idx, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) {
            cover[idx] += val;
            pushUp(idx, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) update(idx << 1, l, mid, ql, qr, val);
        if (qr > mid) update(idx << 1 | 1, mid + 1, r, ql, qr, val);
        pushUp(idx, l, r);
    }

    void update(int l, int r, int val) {
        if (l <= r) update(1, 0, n - 1, l, r, val);
    }

    long long query() const {
        return coveredLen[1];
    }
};

long long solve(int W, int H, const vector<Rect>& rects, int M) {
    vector<long long> xs;
    xs.reserve(2 * rects.size() + 4);
    xs.push_back(1);
    xs.push_back((long long)W + 1);
    for (const auto& r : rects) {
        long long newX1 = max(1LL, r.x1 - M + 1);
        long long newX2 = r.x2 + 1;
        xs.push_back(newX1);
        xs.push_back(newX2);
    }
    if (M > 1) {
        long long boundaryX1 = max(1LL, (long long)W - M + 2);
        long long boundaryX2 = (long long)W + 1;
        if (boundaryX1 <= W) {
            xs.push_back(boundaryX1);
            xs.push_back(boundaryX2);
        }
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    int leafCnt = (int)xs.size() - 1;
    SegTree seg(leafCnt, xs);

    struct Event { long long y, x1, x2; int type; };
    vector<Event> events;
    events.reserve(2 * rects.size() + 2);

    for (const auto& r : rects) {
        long long newX1 = max(1LL, r.x1 - M + 1);
        long long newX2 = r.x2 + 1;
        events.push_back({r.y1, newX1, newX2, 1});
        events.push_back({r.y2 + 1, newX1, newX2, -1});
    }
    if (M > 1) {
        long long boundaryX1 = max(1LL, (long long)W - M + 2);
        long long boundaryX2 = (long long)W + 1;
        if (boundaryX1 <= W) {
            events.push_back({1, boundaryX1, boundaryX2, 1});
            events.push_back({(long long)H + 1, boundaryX1, boundaryX2, -1});
        }
    }

    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.y < b.y;
    });

    long long totalBlocked = 0;
    long long prevY = 1;
    size_t idx = 0;
    while (idx < events.size()) {
        long long curY = events[idx].y;
        if (curY > prevY) {
            totalBlocked += seg.query() * (curY - prevY);
        }
        while (idx < events.size() && events[idx].y == curY) {
            long long x1 = events[idx].x1;
            long long x2 = events[idx].x2;
            int type = events[idx].type;
            int l = lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
            int r = lower_bound(xs.begin(), xs.end(), x2) - xs.begin() - 1;
            seg.update(l, r, type);
            idx++;
        }
        prevY = curY;
    }
    if ((long long)H + 1 > prevY) {
        totalBlocked += seg.query() * ((long long)H + 1 - prevY);
    }

    long long totalStarts = (long long)W * H;
    return totalStarts - totalBlocked;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H, N, M;
    while (cin >> W >> H >> N >> M) {
        vector<Rect> rects(N);
        for (int i = 0; i < N; ++i) {
            cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        }

        long long ans = 0;
        if (M == 1) {
            ans = solve(W, H, rects, M);
        } else {
            long long horizontal = solve(W, H, rects, M);
            vector<Rect> rotatedRects;
            rotatedRects.reserve(N);
            for (const auto& r : rects) {
                rotatedRects.push_back({r.y1, r.x1, r.y2, r.x2});
            }
            long long vertical = solve(H, W, rotatedRects, M);
            ans = horizontal + vertical;
        }

        cout << ans << '\n';
    }
    return 0;
}
