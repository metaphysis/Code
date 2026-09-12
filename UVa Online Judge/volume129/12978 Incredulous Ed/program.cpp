#include <bits/stdc++.h>
using namespace std;

int n, m, cnt;
long long ans;
vector<pair<int, int>> pos;
vector<int> vis;

bool canGo(int cur, int nxt) {
    int x1, y1, x2, y2, x, y, cross;
    x1 = pos[cur].first;
    y1 = pos[cur].second;
    x2 = pos[nxt].first;
    y2 = pos[nxt].second;
    for (int i = 0; i < cnt; i++)
        if (i == cur || i == nxt) continue;
        x = pos[i].first;
        y = pos[i].second;
        cross = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);
        if (cross != 0) continue;
        if (x < min(x1, x2) || x > max(x1, x2)) continue;
        if (y < min(y1, y2) || y > max(y1, y2)) continue;
        if (!vis[i]) return false;
    return true;
}

void dfs(int cur) {
    ans++;
    for (int i = 0; i < cnt; i++) {
        if (vis[i]) continue;
        if (!canGo(cur, i)) continue;
        vis[i] = 1;
        dfs(i);
        vis[i] = 0;
    }
}

int solve() {
    int cas = 1;
    while (cin >> n >> m && (n || m)) {
        pos.clear();
        cnt = n * m;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                pos.push_back({i, j});
        vis.assign(cnt, 0);
        ans = 0;
        for (int i = 0; i < cnt; i++) {
            vis[i] = 1;
            dfs(i);
            vis[i] = 0;
        }
        cout << "Case #" << cas++ << ": " << ans << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
