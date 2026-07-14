// Game of CS 
// UVa ID: 12033
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll sgFunc(ll w, ll c) {
    if (w == 1) return c + 1;
    if (w % 2 == 0) return c;
    return c ^ 1;
}

void dfs(int u, int parent, ll parentWeight,
         vector<vector<pair<int, ll>>>& adj,
         vector<ll>& sg, ll& totalXor) {
    ll childXor = 0;
    for (auto &e : adj[u]) {
        int v = e.first;
        ll w = e.second;
        if (v == parent) continue;
        dfs(v, u, w, adj, sg, totalXor);
        childXor ^= sg[v];
    }
    if (u == 0) {
        totalXor = childXor;
        sg[0] = childXor;
    } else {
        sg[u] = sgFunc(parentWeight, childXor);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n;
        scanf("%d", &n);
        vector<vector<pair<int, ll>>> adj(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            ll w;
            scanf("%d %d %lld", &u, &v, &w);
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        vector<ll> sg(n, 0);
        ll totalXor = 0;
        dfs(0, -1, 0, adj, sg, totalXor);
        printf("Case %d: %s\n", caseNo, totalXor ? "Emily" : "Jolly");
    }
    return 0;
}
