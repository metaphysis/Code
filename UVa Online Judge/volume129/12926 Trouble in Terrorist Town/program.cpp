// Trouble in Terrorist Town
// UVa ID: 12926
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.240s

#include <bits/stdc++.h>
using namespace std;

int N, T;
vector<vector<char>> distrust;
vector<char> vis1, vis2;
vector<int> order;

void dfs1(int u) {
    vis1[u] = 1;
    for (int v = 1; v <= N; ++v)
        if (!vis1[v] && u != v && !distrust[u][v]) dfs1(v);
    order.push_back(u);
}

void dfs2(int u) {
    vis2[u] = 1;
    for (int v = 1; v <= N; ++v)
        if (!vis2[v] && u != v && !distrust[v][u]) dfs2(v);
}

int main() {
    while (scanf("%d%d", &N, &T) == 2) {
        distrust.assign(N + 1, vector<char>(N + 1, 0));
        for (int i = 0; i < T; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            distrust[x][y] = 1;
        }
        long long D;
        scanf("%lld", &D);

        vis1.assign(N + 1, 0);
        vis2.assign(N + 1, 0);
        order.clear();

        for (int i = 1; i <= N; ++i)
            if (!vis1[i]) dfs1(i);

        int sccCount = 0;
        for (int i = N - 1; i >= 0; --i) {
            int u = order[i];
            if (!vis2[u]) {
                ++sccCount;
                dfs2(u);
            }
        }

        printf("%lld\n", (long long)sccCount * D);
    }
    return 0;
}
