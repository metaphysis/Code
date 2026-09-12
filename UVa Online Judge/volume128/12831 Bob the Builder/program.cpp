#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
vector<vector<int>> graph;
vector<int> leftMatch, rightMatch, level;

bool bfs(int n) {
    queue<int> que;
    for (int i = 0; i < n; i++) {
        if (leftMatch[i] == -1) {
            level[i] = 0;
            que.push(i);
        } else {
            level[i] = inf;
        }
    }
    bool found = false;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : graph[u]) {
            int w = rightMatch[v];
            if (w == -1) {
                found = true;
            } else if (level[w] == inf) {
                level[w] = level[u] + 1;
                que.push(w);
            }
        }
    }
    return found;
}

bool dfs(int u) {
    for (int v : graph[u]) {
        int w = rightMatch[v];
        if (w == -1 || (level[w] == level[u] + 1 && dfs(w))) {
            leftMatch[u] = v;
            rightMatch[v] = u;
            return true;
        }
    }
    level[u] = inf;
    return false;
}

int maxMatch(int n) {
    leftMatch.assign(n, -1);
    rightMatch.assign(n, -1);
    level.resize(n);
    int ans = 0;
    while (bfs(n))
        for (int i = 0; i < n; i++)
            if (leftMatch[i] == -1 && dfs(i))
                ans++;
    return ans;
}

int solve() {
    int n, limit;
    cin >> n >> limit;
    vector<int> roots(n), vis(limit + 1, 0);
    queue<int> que;
    for (int i = 0; i < n; i++) {
        cin >> roots[i];
        if (!vis[roots[i]]) {
            vis[roots[i]] = 1;
            que.push(roots[i]);
        }
    }
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int bit = 0; (1 << bit) <= x; bit++) {
            if ((x & (1 << bit)) == 0) continue;
            int y = x + (1 << bit);
            if (y <= limit && !vis[y]) {
                vis[y] = 1;
                que.push(y);
            }
        }
    }
    vector<int> id(limit + 1, -1), nodes;
    for (int x = 1; x <= limit; x++)
        if (vis[x]) {
            id[x] = nodes.size();
            nodes.push_back(x);
        }
    int cnt = nodes.size();
    graph.assign(cnt, vector<int>());
    for (int i = 0; i < cnt; i++) {
        int x = nodes[i];
        for (int bit = 0; (1 << bit) <= x; bit++) {
            if ((x & (1 << bit)) == 0) continue;
            int y = x + (1 << bit);
            if (y <= limit && id[y] != -1)
                graph[i].push_back(id[y]);
        }
    }
    return cnt - maxMatch(cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int ca = 1; ca <= t; ca++)
        cout << "Case " << ca << ": " << solve() << '\n';
    return 0;
}
