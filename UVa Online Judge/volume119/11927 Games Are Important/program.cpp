// Games Are Important
// UVa ID: 11927
// Verdict: Accepted
// Submission Date: 2026-05-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> sg;

int computeSG(int u, const vector<vector<int>>& graph) {
    if (sg[u] != -1) return sg[u];
    vector<bool> seen(graph[u].size() + 1, false);
    for (int v : graph[u]) {
        int sgv = computeSG(v, graph);
        if (sgv < (int)seen.size()) seen[sgv] = true;
    }
    int mex = 0;
    while (seen[mex]) ++mex;
    return sg[u] = mex;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m, n || m) {
        vector<vector<int>> graph(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
        }
        
        sg.assign(n, -1);
        for (int i = 0; i < n; ++i)
            if (sg[i] == -1) computeSG(i, graph);
        
        int xorSum = 0;
        for (int i = 0; i < n; ++i) {
            int stones;
            cin >> stones;
            if (stones & 1) xorSum ^= sg[i];
        }
        
        cout << (xorSum ? "First" : "Second") << '\n';
        
        if (cin.peek() == '\n') cin.ignore();
    }
    return 0;
}
