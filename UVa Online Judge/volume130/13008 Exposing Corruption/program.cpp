// Exposing Corruption
// UVa ID: 13008
// Verdict: Accepted
// Submission Date: 2026-01-23
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;
const int MAXB = 10010;
vector<int> graph[MAXN];
int priceD[MAXN], priceP[MAXN], D, P, R, B;
bool visited[MAXN];

struct Comp {
    int c0, d0, p0, c1, d1, p1;
};

vector<Comp> comps;

void dfs(int u, vector<int>& nodes) {
    visited[u] = true;
    nodes.push_back(u);
    for (int v : graph[u]) if (!visited[v]) dfs(v, nodes);
}

void build() {
    fill(visited, visited + MAXN, false);
    comps.clear();
    for (int i = 1; i <= D + P; ++i) if (!visited[i]) {
        vector<int> nodes;
        dfs(i, nodes);
        
        // BFS染色
        vector<int> color(nodes.size(), -1);
        color[0] = 0;
        queue<int> q; q.push(0);
        while (!q.empty()) {
            int idx = q.front(); q.pop();
            int u = nodes[idx];
            for (int v : graph[u]) {
                auto it = find(nodes.begin(), nodes.end(), v);
                if (it == nodes.end()) continue;
                int vIdx = it - nodes.begin();
                if (color[vIdx] == -1) color[vIdx] = 1 - color[idx], q.push(vIdx);
            }
        }
        
        // 计算两种方案
        Comp comp = {0, 0, 0, 0, 0, 0};
        for (int j = 0; j < nodes.size(); ++j) {
            int node = nodes[j], init = (node <= D) ? 0 : 1;
            int final0 = color[j], final1 = 1 - final0;
            
            // 方案0
            if (init == 0) {
                if (final0 == 0) comp.d0++;
                else comp.p0++, comp.c0 += priceD[node];
            } else {
                if (final0 == 0) comp.d0++, comp.c0 += priceP[node];
                else comp.p0++;
            }
            
            // 方案1  
            if (init == 0) {
                if (final1 == 0) comp.d1++;
                else comp.p1++, comp.c1 += priceD[node];
            } else {
                if (final1 == 0) comp.d1++, comp.c1 += priceP[node];
                else comp.p1++;
            }
        }
        comps.push_back(comp);
    }
}

int solve(bool forDSP) {
    vector<int> dp(B + 1, 0);
    for (const Comp& c : comps) for (int b = B; b >= 0; --b) {
        if (b >= c.c0) dp[b] = max(dp[b], dp[b - c.c0] + (forDSP ? c.d0 : c.p0));
        if (b >= c.c1) dp[b] = max(dp[b], dp[b - c.c1] + (forDSP ? c.d1 : c.p1));
    }
    return dp[B];
}

int main() {
    while (cin >> D >> P >> R >> B) {
        for (int i = 0; i < MAXN; ++i) graph[i].clear();
        for (int i = 1; i <= D; ++i) cin >> priceD[i];
        for (int j = 1; j <= P; ++j) cin >> priceP[j + D];
        for (int i = 0; i < R; ++i) {
            int x, y; cin >> x >> y;
            graph[x].push_back(y + D);
            graph[y + D].push_back(x);
        }
        build();
        cout << solve(true) << " " << solve(false) << endl;
    }
    return 0;
}
