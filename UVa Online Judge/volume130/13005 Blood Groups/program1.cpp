// Blood Groups
// UVa ID: 13005
// Verdict: Accepted
// Submission Date: 2026-06-22
// UVa Run Time: 0.200s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool canMatch(const vector<set<int>>& parents, const vector<int>& query) {
    int N = parents.size();
    int B = query.size();

    // 查询为空（O型）：所有父母必须能贡献O（即血型大小<N）
    if (B == 0) {
        for (int i = 0; i < N; ++i)
            if ((int)parents[i].size() == N) return false;
        return true;
    }

    // 建立二分图：左部父母(0..N-1)，右部查询抗原(0..B-1)
    vector<vector<bool>> adj(N, vector<bool>(B, false));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < B; ++j)
            if (parents[i].count(query[j]))
                adj[i][j] = true;

    // 匈牙利算法
    vector<int> matchR(B, -1);
    function<bool(int, vector<bool>&)> dfs = [&](int u, vector<bool>& seen) -> bool {
        for (int v = 0; v < B; ++v) {
            if (adj[u][v] && !seen[v]) {
                seen[v] = true;
                if (matchR[v] == -1 || dfs(matchR[v], seen)) {
                    matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    };

    int matches = 0;
    for (int u = 0; u < N; ++u) {
        vector<bool> seen(B, false);
        if (dfs(u, seen)) ++matches;
    }
    return matches == B;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    while (cin >> N >> Q) {
        vector<set<int>> parents(N);
        for (int i = 0; i < N; ++i) {
            int B;
            cin >> B;
            for (int j = 0; j < B; ++j) {
                int c;
                cin >> c;
                parents[i].insert(c);
            }
        }
        for (int q = 0; q < Q; ++q) {
            int B;
            cin >> B;
            vector<int> query(B);
            for (int i = 0; i < B; ++i) cin >> query[i];
            cout << (canMatch(parents, query) ? 'Y' : 'N') << '\n';
        }
    }
    return 0;
}
