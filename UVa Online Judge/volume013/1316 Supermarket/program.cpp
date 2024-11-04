// Supermarket
// UVa ID: 1316
// Verdict: Accepted
// Submission Date: 2024-11-04
// UVa Run Time: 0.020s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10010;

struct item {
    int px, dx;
    bool operator<(const item it) const {
        if (px != it.px) return px > it.px;
        return dx > it.dx;
    }
} its[MAXN];

int used[MAXN], link[MAXN];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++) cin >> its[i].px >> its[i].dx;
        sort(its, its + n);
        for (int i = 0; i <= n; i++) used[i] = 0, link[i] = i;
        int profit = 0;
        for (int i = 0; i < n; i++) {
            int dx = its[i].dx;
            if (dx > n) dx = n;
            int idx = link[dx];
            while (idx) if (!used[idx]) break; else idx--;
            if (idx) {
                profit += its[i].px;
                used[idx] = 1;
                link[dx] = idx - 1;
            }
        }
        cout << profit << '\n';
    }
    return 0;
}
