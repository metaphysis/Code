// Balloon
// UVa ID: 12647
// Verdict: Accepted
// Submission Date: 2026-06-12
// UVa Run Time: 0.120s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1000010;
const int MAXN = 100010;

int cover[MAXC << 2];
int f[MAXN];
int ansX[MAXN];
int n, m;

struct Segment {
    int x1, y1, x2, y2;
    bool operator<(const Segment &b) const {
        return y1 < b.y1;
    }
} seg[MAXN];

void pushDown(int rt) {
    if (cover[rt] != -1) {
        cover[rt << 1] = cover[rt << 1 | 1] = cover[rt];
        cover[rt] = -1;
    }
}

void update(int L, int R, int idx, int l, int r, int rt) {
    if (L <= l && r <= R) {
        cover[rt] = idx;
        return;
    }
    int m = (l + r) >> 1;
    pushDown(rt);
    if (L <= m) update(L, R, idx, l, m, rt << 1);
    if (R > m) update(L, R, idx, m + 1, r, rt << 1 | 1);
}

int query(int x, int l, int r, int rt) {
    if (cover[rt] >= 0) return cover[rt];
    int m = (l + r) >> 1;
    if (x <= m) return query(x, l, m, rt << 1);
    else return query(x, m + 1, r, rt << 1 | 1);
}

void solve() {
    sort(seg, seg + n + 1);
    memset(cover, -1, sizeof(cover));
    for (int i = n; i >= 0; --i) {
        if (seg[i].y1 == seg[i].y2) {
            f[i] = i;
        } else {
            int k = query(seg[i].x1, 0, MAXC, 1);
            f[i] = f[k];
            if (seg[k].y1 == seg[k].y2) ansX[i] = seg[i].x1;
            else ansX[i] = ansX[k];
        }
        int L = seg[i].x1, R = seg[i].x2;
        if (L > R) swap(L, R);
        update(L, R, i, 0, MAXC, 1);
    }
}

void answerQuery(int x) {
    int k = query(x, 0, MAXC, 1);
    if (seg[k].y1 != seg[k].y2) x = ansX[k];
    if (f[k] == n) cout << x << '\n';
    else cout << x << ' ' << seg[f[k]].y1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i) {
            cin >> seg[i].x1 >> seg[i].y1 >> seg[i].x2 >> seg[i].y2;
            if (seg[i].y1 < seg[i].y2) {
                swap(seg[i].x1, seg[i].x2);
                swap(seg[i].y1, seg[i].y2);
            }
        }
        seg[n].x1 = 0;
        seg[n].y1 = MAXC + 1;
        seg[n].x2 = MAXC;
        seg[n].y2 = MAXC + 1;
        solve();
        while (m--) {
            int x;
            cin >> x;
            answerQuery(x);
        }
    }
    return 0;
}
