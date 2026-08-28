#include <bits/stdc++.h>
using namespace std;

const int inf = 50010;

int n, m;
vector<vector<int> > graph;
vector<int> par, ord, bad, fVal, gVal;

void buildTree() {
    par.assign(n + 1, 0);
    ord.clear();
    ord.reserve(n);
    ord.push_back(1);
    for (int i = 0; i < (int)ord.size(); i++) {
        int u = ord[i];
        for (int v : graph[u])
            if (v != par[u]) {
                par[v] = u;
                ord.push_back(v);
            }
    }
}

void calcDp() {
    fVal.assign(n + 1, 0);
    gVal.assign(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        if (bad[u]) {
            fVal[u] = 0;
            gVal[u] = 0;
            continue;
        }
        if (u != 1 && graph[u].size() == 1) {
            fVal[u] = 1;
            gVal[u] = 0;
            continue;
        }
        if (u == 1 || graph[u].size() == 2) {
            int v;
            if (u == 1) v = graph[u][0];
            else v = graph[u][0] != par[u] ? graph[u][0] : graph[u][1];
            if (bad[v]) bad[u] = 1;
            fVal[u] = fVal[v];
            gVal[u] = gVal[v];
            continue;
        }
        int l = graph[u][0] != par[u] ? graph[u][0] : graph[u][1];
        int r = graph[u][0] + graph[u][1] + graph[u][2] - par[u] - l;
        if (bad[l] || bad[r]) bad[u] = 1;
        if (bad[l] && bad[r]) gVal[u] = inf;
        else gVal[u] = min(gVal[l] + gVal[r], min(gVal[l] + fVal[r], gVal[r] + fVal[l]));
        fVal[u] = min(fVal[l] + fVal[r], gVal[u] + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        graph.assign(n + 1, vector<int>());
        bad.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            int cnt;
            cin >> cnt;
            graph[i].resize(cnt);
            for (int j = 0; j < cnt; j++) cin >> graph[i][j];
        }
        for (int i = 0; i < m; i++) {
            int u;
            cin >> u;
            bad[u] = 1;
        }
        buildTree();
        calcDp();
        cout << fVal[1] << '\n';
    }
    return 0;
}
