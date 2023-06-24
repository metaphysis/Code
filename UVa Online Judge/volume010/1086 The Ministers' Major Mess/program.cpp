// The Ministers' Major Mess
// UVa ID: 1085
// Verdict: Accepted
// Submission Date: 2023-06-24
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;

vector<int> g[MAXN];
int B, M, dfn[MAXN], low[MAXN];
int scc[MAXN], cscc, dfstime;
stack<int> s;

void dfs(int u) {
    low[u] = dfn[u] = ++dfstime;
    s.push(u);
    for (auto v : g[u]) {
        if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++cscc;
        while (true) {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
}

void addEdge(int u, int v) { g[u].push_back(v); }

bool satisfied() {
    for (int i = 0; i < B; i++) scc[i] = dfn[i] = 0;
    dfstime = cscc = 0;
    while (!s.empty()) s.pop();
    for (int i = 0; i < B; i++)
        if (!dfn[i])
            dfs(i);
    for (int i = 0; i < B; i += 2)
        if (scc[i] == scc[i ^ 1])
            return false;
    return true;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    while (cin >> B >> M, B) {
        B <<= 1;
        for (int i = 0; i < B; i++) g[i].clear();
        char yn;
        int vote[4], k, idx;
        for (int i = 0; i < M; i++) {
            cin >> k;
            for (int j = 0; j < k; j++) {
                cin >> idx >> yn;
                vote[j] = ((idx - 1) << 1) | (yn == 'y');
            }
            if (k <= 2) {
                for (int p = 0; p < k; p++)
                    addEdge(vote[p] ^ 1, vote[p]);
            } else {
                for (int p = 0; p < k; p++) {
                    for (int q = 0; q < k; q++) {
                        if (p == q) continue;
                        addEdge(vote[p] ^ 1, vote[q]);
                    }
                }
            }
        }
        cout << "Case " << cases++ << ": ";
        if (!satisfied()) cout << "impossible";
        else {
            for (int i = 0; i < B; i += 2) {
                int r = 0;
                g[i].push_back(i ^ 1);
                if (satisfied()) r |= 1;
                g[i].pop_back();
                g[i ^ 1].push_back(i);
                if (satisfied()) r |= 2;
                g[i ^ 1].pop_back();
                cout << "-yn?"[r];
            }
        }
        cout << '\n';
    }
    return 0;
}
