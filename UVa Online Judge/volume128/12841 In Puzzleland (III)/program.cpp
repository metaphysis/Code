// In Puzzleland (III)
// UVa ID: 12841
// Verdict: Accepted
// Submission Date: 2023-01-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int T, N, M, s, t, used[32], mask, MASK;
vector<int> g[32];

int bfs(int x, int m) {
    queue<int> q;
    q.push(x);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : g[u]) {
            if (m & (1 << v)) continue;
            m |= (1 << v);
            q.push(v);
        }
    }
    return __builtin_popcount(m) == N;
}

int dfs(int idx, int u) {
    if (mask == MASK) {
        for (int i = 0; i < N; i++) cout << (char)(used[i] + 'A');
        cout << '\n';
        return 1;
    }
    for (auto v : g[u]) {
        if (mask & (1 << v)) continue;
        if (v == t && __builtin_popcount(mask) != N - 1) continue;
        if (!bfs(v, mask | (1 << v))) continue;
        used[idx] = v;
        mask |= (1 << v);
        if (dfs(idx + 1, v)) return 1;
        mask ^= (1 << v);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cin >> N >> M;
        for (int i = 0; i < 26; i++) g[i].clear();
        char u, v;
        MASK = 0;
        memset(used, 0, sizeof used);
        for (int i = 0; i < N; i++) {
            cin >> u;
            MASK |= (1 << (u - 'A'));
            if (i == 0) s = u - 'A';
            if (i == N - 1) t = u - 'A';
        }
        for (int i = 0; i < M; i++) {
            cin >> u >> v;
            g[u - 'A'].push_back(v - 'A');
            g[v - 'A'].push_back(u - 'A');
        }
        for (int i = 0; i < 26; i++) sort(g[i].begin(), g[i].end());
        cout << "Case " << cs << ": ";
        mask = (1 << s), used[0] = s;
        if (!dfs(1, s)) cout << "impossible\n";
    }
    return 0;
}
