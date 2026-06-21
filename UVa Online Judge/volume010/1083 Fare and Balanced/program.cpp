// Fare and Balanced
// UVa ID: 1083
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.260s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct Edge {
    int u, v, c, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R;
    int caseNo = 0;
    while (cin >> N >> R && (N || R)) {
        ++caseNo;
        vector<Edge> edges;
        edges.reserve(R);
        vector<vector<int>> adj(N + 1), radj(N + 1);
        vector<int> indeg(N + 1, 0), outdeg(N + 1, 0);

        for (int i = 1; i <= R; ++i) {
            int x, y, c;
            cin >> x >> y >> c;
            edges.push_back({x, y, c, i});
            adj[x].push_back(i - 1);
            radj[y].push_back(i - 1);
            indeg[y]++;
            outdeg[x]++;
        }

        // 拓扑排序
        vector<int> topo;
        queue<int> q;
        for (int i = 1; i <= N; ++i)
            if (indeg[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (int id : adj[u]) {
                int v = edges[id].v;
                if (--indeg[v] == 0) q.push(v);
            }
        }

        // 正向：从1到各点的最小最大路径代价
        vector<ll> min1(N + 1, INF), max1(N + 1, -INF);
        min1[1] = max1[1] = 0;
        for (int u : topo) {
            if (min1[u] == INF) continue;
            for (int id : adj[u]) {
                int v = edges[id].v, c = edges[id].c;
                min1[v] = min(min1[v], min1[u] + c);
                max1[v] = max(max1[v], max1[u] + c);
            }
        }

        // 反向拓扑序
        vector<int> rtopo;
        queue<int> rq;
        for (int i = 1; i <= N; ++i)
            if (outdeg[i] == 0) rq.push(i);
        while (!rq.empty()) {
            int u = rq.front(); rq.pop();
            rtopo.push_back(u);
            for (int id : radj[u]) {
                int v = edges[id].u;
                if (--outdeg[v] == 0) rq.push(v);
            }
        }

        // 反向：从各点到N的最小最大路径代价
        vector<ll> min2(N + 1, INF), max2(N + 1, -INF);
        min2[N] = max2[N] = 0;
        for (int u : rtopo) {
            if (min2[u] == INF) continue;
            for (int id : radj[u]) {
                int v = edges[id].u, c = edges[id].c;
                min2[v] = min(min2[v], min2[u] + c);
                max2[v] = max(max2[v], max2[u] + c);
            }
        }

        ll L = max1[N]; // 最长路径代价

        // 判断是否所有路径代价已经相同
        if (min1[N] == max1[N] && min1[N] == L) {
            cout << "Case " << caseNo << ": 0 " << L << "\n";
            continue;
        }

        // 判断每个节点的前缀/后缀是否唯一
        vector<bool> preUnique(N + 1, false), sufUnique(N + 1, false);
        for (int i = 1; i <= N; ++i) {
            if (min1[i] != INF && min1[i] == max1[i]) preUnique[i] = true;
            if (min2[i] != INF && min2[i] == max2[i]) sufUnique[i] = true;
        }

        // 标记可收费边
        vector<bool> tollable(R, false);
        vector<ll> baseCost(R, 0);
        for (int id = 0; id < R; ++id) {
            int u = edges[id].u, v = edges[id].v, c = edges[id].c;
            if (preUnique[u] && sufUnique[v]) {
                ll base = min1[u] + c + min2[v]; // 唯一
                if (base < L) {
                    tollable[id] = true;
                    baseCost[id] = base;
                }
            }
        }

        // 状态DP：状态0未收费，状态1已收费
        vector<ll> min0(N + 1, INF), max0(N + 1, -INF);
        vector<ll> min1st(N + 1, INF), max1st(N + 1, -INF);
        min0[1] = max0[1] = 0;

        // 记录选中的收费边
        vector<pair<int, ll>> chosen; // (road编号, toll)

        for (int u : topo) {
            // 先处理状态0
            if (min0[u] != INF) {
                for (int id : adj[u]) {
                    int v = edges[id].v, c = edges[id].c;
                    if (tollable[id]) {
                        // 收费，进入状态1
                        ll newMin = min0[u] + c;
                        ll newMax = max0[u] + c;
                        min1st[v] = min(min1st[v], newMin);
                        max1st[v] = max(max1st[v], newMax);
                        // 选中这条边
                        ll toll = L - baseCost[id];
                        chosen.push_back({edges[id].id, toll});
                    } else {
                        // 不收费，保持状态0
                        min0[v] = min(min0[v], min0[u] + c);
                        max0[v] = max(max0[v], max0[u] + c);
                    }
                }
            }
            // 处理状态1（不能再次收费）
            if (min1st[u] != INF) {
                for (int id : adj[u]) {
                    int v = edges[id].v, c = edges[id].c;
                    min1st[v] = min(min1st[v], min1st[u] + c);
                    max1st[v] = max(max1st[v], max1st[u] + c);
                }
            }
        }

        bool ok = true;
        // 检查状态0到达N的路径：必须全部等于L
        if (min0[N] != INF) {
            if (min0[N] != max0[N] || min0[N] != L) ok = false;
        }
        // 检查状态1到达N的路径：必须全部等于L（因为过路费已补足）
        if (min1st[N] != INF) {
            if (min1st[N] != max1st[N] || min1st[N] != L) ok = false;
        }
        // 同时必须保证所有路径至少有一种状态（即N可达性）
        if (min0[N] == INF && min1st[N] == INF) ok = false;

        if (!ok) {
            cout << "Case " << caseNo << ": No solution\n";
        } else {
            cout << "Case " << caseNo << ": " << chosen.size() << " " << L << "\n";
            for (auto &p : chosen)
                cout << p.first << " " << p.second << "\n";
        }
    }
    return 0;
}
