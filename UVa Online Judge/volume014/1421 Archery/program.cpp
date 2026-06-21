// Archery
// UVa ID: 1421
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 5000 + 5;
const double eps = 1e-6;

struct Target {
    int d, l, r;
    bool operator < (const Target &rhs) const {
        return d < rhs.d;
    }
} tar[maxn];

int T, w, n;

// 判定射手位置 cur 是否可行
// 返回  0 : 可行
// 返回 -1 : 需要左移（cur 偏大）
// 返回  1 : 需要右移（cur 偏小）
int judge(double cur) {
    // k = 1 / tan(theta)
    double k1 = (tar[0].l - cur) / tar[0].d;
    double k2 = (tar[0].r - cur) / tar[0].d;
    double k3, k4;
    for (int i = 1; i < n; ++i) {
        k3 = (tar[i].l - cur) / tar[i].d;
        k4 = (tar[i].r - cur) / tar[i].d;
        if (k3 - k2 > eps) return -1;  // 区间在上方，点要左移
        else if (k4 - k1 < -eps) return 1; // 区间在下方，点要右移
        k1 = max(k1, k3);
        k2 = min(k2, k4);
    }
    return 0;
}

bool solve() {
    double L = 0, R = w;
    while (R - L > eps) {
        double mid = (L + R) / 2;
        int t = judge(mid);
        if (t == 0) return true;
        else if (t == 1) L = mid;
        else R = mid;
    }
    return false;
}

int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &w, &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &tar[i].d, &tar[i].l, &tar[i].r);
        }
        sort(tar, tar + n);
        bool ans = solve();
        printf("%s\n", ans ? "YES" : "NO");
    }
    return 0;
}
