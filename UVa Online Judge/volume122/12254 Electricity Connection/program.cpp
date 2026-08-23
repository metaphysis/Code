#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
int pl, pw, n, fullMask;
vector<string> grid;
vector<int> term;
vector<vector<int> > dp;
int dirX[4] = {-1, 1, 0, 0};
int dirY[4] = {0, 0, -1, 1};

int nodeCost(int x, int y) {
    if (grid[x][y] == '.')
        return pl;
    if (grid[x][y] == 'W')
        return pw;
    return 0;
}

void relax(int mask) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
    for (int i = 0; i < 64; ++i)
        if (dp[mask][i] < inf)
            que.push(make_pair(dp[mask][i], i));
    while (!que.empty()) {
        int dis = que.top().first, id = que.top().second;
        que.pop();
        if (dis != dp[mask][id])
            continue;
        int x = id / 8, y = id % 8;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dirX[d], ny = y + dirY[d];
            if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8)
                continue;
            int nid = nx * 8 + ny;
            int nd = dis + 1 + nodeCost(nx, ny);
            if (nd < dp[mask][nid]) {
                dp[mask][nid] = nd;
                que.push(make_pair(nd, nid));
            }
        }
    }
}

int solve() {
    n = static_cast<int>(term.size());
    fullMask = (1 << n) - 1;
    dp.assign(1 << n, vector<int>(64, inf));
    for (int i = 0; i < n; ++i)
        dp[1 << i][term[i]] = 0;
    for (int mask = 1; mask <= fullMask; ++mask) {
        for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
            int other = mask ^ sub;
            if (!other || sub > other)
                continue;
            for (int v = 0; v < 64; ++v)
                dp[mask][v] = min(dp[mask][v], dp[sub][v] + dp[other][v] - nodeCost(v / 8, v % 8));
        }
        relax(mask);
    }
    int ans = inf;
    for (int v = 0; v < 64; ++v)
        ans = min(ans, dp[fullMask][v]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; ++cs) {
        cin >> pl >> pw;
        grid.assign(8, string());
        term.clear();
        for (int i = 0; i < 8; ++i) {
            cin >> grid[i];
            for (int j = 0; j < 8; ++j)
                if (grid[i][j] == 'G' || grid[i][j] == 'H')
                    term.push_back(i * 8 + j);
        }
        cout << "Case " << cs << ": " << solve() << '\n';
    }
    return 0;
}
