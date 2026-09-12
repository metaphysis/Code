#include <bits/stdc++.h>
using namespace std;

const int mod = 912, maxN = 2005;
int comb[maxN][maxN];

int getPath(int x1, int y1, int x2, int y2) {
    int dx, dy;
    dx = x2 - x1;
    dy = y2 - y1;
    if (dx < 0 || dy < 0) return 0;
    return comb[dx + dy][dx];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < maxN; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++)
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
    }
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int r, col, q;
        cin >> r >> col >> q;
        cout << "Case " << tc << '\n';
        for (int id = 1; id <= q; id++) {
            int a, b, c, d, bad = 0;
            cin >> a >> b >> c >> d;
            if (a == 0 && b == 0) {
                cout << "   Query " << id << ": 0\n";
                continue;
            }
            for (int j = b; j <= d; j++) {
                if (a == 0) break;
                int pre, suf;
                pre = getPath(0, 0, a - 1, j);
                suf = getPath(a, j, r - 1, col - 1);
                bad = (bad + pre * suf) % mod;
            }
            for (int i = a; i <= c; i++) {
                if (b == 0) break;
                int pre, suf;
                pre = getPath(0, 0, i, b - 1);
                suf = getPath(i, b, r - 1, col - 1);
                bad = (bad + pre * suf) % mod;
            }
            int all, ans;
            all = getPath(0, 0, r - 1, col - 1);
            ans = (all - bad + mod) % mod;
            cout << "   Query " << id << ": " << ans << '\n';
        }
    }
    return 0;
}
