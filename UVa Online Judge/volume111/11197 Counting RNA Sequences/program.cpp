#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

ull countIs(const vector<int>& nodes, const vector<vector<int>>& adj) {
    int m = nodes.size();
    vector<int> id(50, -1), last(m);
    vector<vector<int>> graph(m);
    for (int i = 0; i < m; i++) id[nodes[i]] = i;
    for (int i = 0; i < m; i++) {
        for (int v : adj[nodes[i]]) {
            int to = id[v];
            if (to != -1) graph[i].push_back(to);
        }
    }
    for (int i = 0; i < m; i++) {
        last[i] = i;
        for (int v : graph[i]) {
            if (v > i) last[i] = max(last[i], v);
        }
    }
    vector<int> active;
    vector<ull> dp(1, 1);
    for (int i = 0; i < m; i++) {
        int oldW = active.size(), keepW = 0;
        bool addCur = last[i] > i;
        vector<int> keep(oldW, -1), nextActive;
        for (int j = 0; j < oldW; j++) {
            if (last[active[j]] > i) {
                keep[j] = keepW++;
                nextActive.push_back(active[j]);
            }
        }
        int newW = keepW + (addCur ? 1 : 0);
        unsigned int nearMask = 0;
        for (int j = 0; j < oldW; j++) {
            bool linked = false;
            for (int v : graph[i]) {
                if (v == active[j]) {
                    linked = true;
                    break;
                }
            }
            if (linked) nearMask |= 1U << j;
        }
        vector<ull> nextDp(1ULL << newW, 0);
        for (unsigned int mask = 0; mask < dp.size(); mask++) {
            unsigned int nextMask = 0;
            for (int j = 0; j < oldW; j++) {
                if ((mask & (1U << j)) && keep[j] != -1) nextMask |= 1U << keep[j];
            }
            nextDp[nextMask] += dp[mask];
            if ((mask & nearMask) == 0) {
                if (addCur) nextDp[nextMask | (1U << keepW)] += dp[mask];
                else nextDp[nextMask] += dp[mask];
            }
        }
        if (addCur) nextActive.push_back(i);
        active = nextActive;
        dp.swap(nextDp);
    }
    ull result = 0;
    for (ull value : dp) result += value;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, tc = 0;
    while (cin >> n && n) {
        vector<string> structures(n);
        for (int i = 0; i < n; i++) cin >> structures[i];
        int len = structures[0].size();
        vector<vector<int>> adj(len);
        bool hasEdge[50][50] = {};
        for (int i = 0; i < n; i++) {
            vector<int> stk;
            for (int j = 0; j < len; j++) {
                if (structures[i][j] == '(') stk.push_back(j);
                else if (structures[i][j] == ')') {
                    int u = stk.back(), v = j;
                    stk.pop_back();
                    if (!hasEdge[u][v]) {
                        hasEdge[u][v] = hasEdge[v][u] = true;
                        adj[u].push_back(v);
                        adj[v].push_back(u);
                    }
                }
            }
        }
        vector<int> color(len, -1);
        ull ans = 1;
        bool ok = true;
        for (int i = 0; i < len; i++) {
            if (color[i] != -1) continue;
            vector<int> nodes;
            queue<int> que;
            color[i] = 0;
            que.push(i);
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                nodes.push_back(u);
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        que.push(v);
                    } else if (color[v] == color[u]) ok = false;
                }
            }
            if (nodes.size() == 1) ans *= 4;
            else ans *= countIs(nodes, adj) * 2;
        }
        if (!ok) ans = 0;
        cout << "Case " << ++tc << ": " << ans << '\n';
    }
    return 0;
}
