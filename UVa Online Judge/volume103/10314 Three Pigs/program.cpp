#include <bits/stdc++.h>
using namespace std;

struct Solver {
    int m, best, now;
    vector<vector<int> > a;
    vector<vector<bool> > vis;
    vector<pair<int, int> > path, bestPath;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    bool check(int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < m && a[x][y] != 2;
    }

    bool bound(int x, int y) {
        vector<vector<bool> > seen(m, vector<bool>(m));
        queue<pair<int, int> > que;
        int sum = -a[x][y];
        seen[x][y] = true;
        que.push(make_pair(x, y));
        while (!que.empty()) {
            pair<int, int> p = que.front();
            que.pop();
            for (int k = 0; k < 4; k++) {
                int nx = p.first + dx[k], ny = p.second + dy[k];
                if (!check(nx, ny) || seen[nx][ny]) continue;
                if (vis[nx][ny] && (nx != x || ny != y)) continue;
                seen[nx][ny] = true;
                sum += a[nx][ny];
                que.push(make_pair(nx, ny));
            }
        }
        if (!seen[m - 1][m - 1]) return false;
        return now + sum > best;
    }

    void dfs(int x, int y) {
        if (x == m - 1 && y == m - 1) {
            if (now > best) {
                best = now;
                bestPath = path;
            }
            return;
        }
        if (!bound(x, y)) return;
        vector<pair<int, int> > nxt;
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (check(nx, ny) && !vis[nx][ny]) nxt.push_back(make_pair(nx, ny));
        }
        sort(nxt.begin(), nxt.end(), [&](const pair<int, int>& p, const pair<int, int>& q) {
            int vp = a[p.first][p.second], vq = a[q.first][q.second];
            int dp = abs(p.first - m + 1) + abs(p.second - m + 1);
            int dq = abs(q.first - m + 1) + abs(q.second - m + 1);
            if (vp != vq) return vp > vq;
            return dp < dq;
        });
        for (int i = 0; i < (int)nxt.size(); i++) {
            int nx = nxt[i].first, ny = nxt[i].second;
            vis[nx][ny] = true;
            now += a[nx][ny];
            path.push_back(nxt[i]);
            dfs(nx, ny);
            path.pop_back();
            now -= a[nx][ny];
            vis[nx][ny] = false;
        }
    }

    int findPath() {
        if (a[0][0] == 2 || a[m - 1][m - 1] == 2) return -1;
        vis.assign(m, vector<bool>(m));
        path.clear();
        bestPath.clear();
        best = -1;
        now = a[0][0];
        vis[0][0] = true;
        path.push_back(make_pair(0, 0));
        dfs(0, 0);
        if (best == -1) return -1;
        for (int i = 0; i < (int)bestPath.size(); i++) {
            int x = bestPath[i].first, y = bestPath[i].second;
            a[x][y] = 0;
        }
        return best;
    }

    int solve() {
        int ans = 0;
        for (int i = 0; i < 3; i++) {
            int got = findPath();
            if (got == -1) return -1;
            ans += got;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        Solver sol;
        cin >> sol.m;
        sol.a.assign(sol.m, vector<int>(sol.m));
        for (int i = 0; i < sol.m; i++)
            for (int j = 0; j < sol.m; j++) cin >> sol.a[i][j];
        cout << sol.solve() << '\n';
    }
    return 0;
}
