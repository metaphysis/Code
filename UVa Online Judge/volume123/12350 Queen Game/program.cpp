#include <bits/stdc++.h>
using namespace std;

int sg[26][2600], dif[26][789];

void init() {
    bool vis[7000];
    int i, j, k, mex;
    for (i = 1; i <= 25; i++) for (j = 1; j <= 2590; j++) {
        memset(vis, 0, sizeof(vis));
        for (k = 1; k < i; k++) vis[sg[i - k][j]] = true;
        for (k = 1; k < j; k++) vis[sg[i][j - k]] = true;
        for (k = 1; k < i && k < j; k++) vis[sg[i - k][j - k]] = true;
        mex = 0;
        while (vis[mex]) mex++;
        sg[i][j] = mex;
    }
    for (i = 1; i <= 768; i++) for (k = 1; k <= 25; k++) dif[k][i - 1] = sg[k][1799 + i] - sg[k][1799];
}

long long getSg(int x, long long y) {
    long long q, r;
    if (y < 1800) return sg[x][y];
    q = (y - 1800) / 768;
    r = (y - 1800) % 768;
    return sg[x][1799] + q * 768 + dif[x][r];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, r, n, x;
    long long c, y, ans;
    init();
    cin >> t;
    while (t--) {
        cin >> r >> c >> n;
        ans = 0;
        while (n--) {
            cin >> x >> y;
            ans ^= getSg(x, y);
        }
        if (ans) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
