#include <bits/stdc++.h>
using namespace std;

const int mod = 2552;
const int maxN = 2000;
int comb[maxN + 1][maxN + 1];

int getWays(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1;
    return comb[dx + dy][dx];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i <= maxN; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++)
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
    }
    int t;
    cin >> t;
    while (t--) {
        int w, h, k;
        cin >> w >> h >> k;
        while (k--) {
            int q, ans;
            cin >> q;
            ans = comb[w + h][w];
            while (q--) {
                int a, b, c, d, cur;
                cin >> a >> b >> c >> d;
                cur = 1LL * getWays(0, 0, a, b) * getWays(c, d, w, h) % mod;
                ans -= cur;
                if (ans < 0) ans += mod;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
