// Voting Duels
// UVa ID: 12949
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.000s


#include <bits/stdc++.h>
using namespace std;

// 计算传递闭包，返回每个节点可达的集合（位掩码）
vector<int> computeReach(const vector<int>& adj, int n) {
    vector<int> reach = adj;
    for (int i = 0; i < n; ++i) reach[i] |= (1 << i);
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            if (reach[i] & (1 << k))
                reach[i] |= reach[k];
    return reach;
}

// DFS搜索可行集合S
bool dfs(int S, int cover, int full, const vector<int>& reach, const vector<int>& tie, int n) {
    if (cover == full) return true;
    int cand = 0;
    for (int v = 0; v < n; ++v) {
        if (S & (1 << v)) continue;
        if ((tie[v] & S) == S) cand |= (1 << v);
    }
    if (cand == 0) return false;
    // 剪枝：所有候选节点的可达并集仍不能覆盖全部
    int totalReach = 0;
    for (int v = 0; v < n; ++v) if (cand & (1 << v)) totalReach |= reach[v];
    if ((cover | totalReach) != full) return false;
    // 按覆盖新节点的数量降序排序候选
    vector<int> list;
    for (int v = 0; v < n; ++v) if (cand & (1 << v)) list.push_back(v);
    sort(list.begin(), list.end(), [&](int a, int b) {
        int ca = __builtin_popcount(reach[a] & ~cover);
        int cb = __builtin_popcount(reach[b] & ~cover);
        return ca > cb;
    });
    for (int v : list) {
        int newS = S | (1 << v);
        int newCover = cover | reach[v];
        if (dfs(newS, newCover, full, reach, tie, n)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, b;
    char targetChar;
    while (cin >> n >> b >> targetChar) {
        int target = targetChar - 'a';
        vector<int> blocSize(b);
        vector<string> pref(b);
        for (int i = 0; i < b; ++i) {
            cin >> blocSize[i] >> pref[i];
        }
        // 计算每对候选人的胜负和平局
        vector<vector<int>> vote(n, vector<int>(n, 0)); // vote[i][j] 表示i vs j时i的票数，仅当i<j时有效
        for (int i = 0; i < b; ++i) {
            int s = blocSize[i];
            const string& p = pref[i];
            vector<int> pos(n);
            for (int j = 0; j < n; ++j) pos[p[j] - 'a'] = j;
            for (int u = 0; u < n; ++u) {
                for (int v = u + 1; v < n; ++v) {
                    if (pos[u] < pos[v]) vote[u][v] += s;
                    else vote[v][u] += s;
                }
            }
        }
        vector<int> adj(n, 0), tie(n, 0); // adj[i]表示i能战胜的节点，tie[i]表示与i平局的节点
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if (vote[u][v] > vote[v][u]) { // u胜v
                    adj[u] |= (1 << v);
                } else if (vote[v][u] > vote[u][v]) { // v胜u
                    adj[v] |= (1 << u);
                } else { // 平局
                    tie[u] |= (1 << v);
                    tie[v] |= (1 << u);
                }
            }
        }
        // 计算传递闭包
        vector<int> reach = computeReach(adj, n);
        int full = (1 << n) - 1;
        int startS = 1 << target;
        int startCover = reach[target];
        bool ans = dfs(startS, startCover, full, reach, tie, n);
        cout << (ans ? 'Y' : 'N') << '\n';
    }
    return 0;
}
