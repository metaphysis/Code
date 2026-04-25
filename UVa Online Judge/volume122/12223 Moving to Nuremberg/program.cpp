// Moving to Nuremberg
// UVa ID: 12223
// Verdict: Accepted
// Submission Date: 2026-04-20
// UVa Run Time: 0.120s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 50005;

struct Edge {
    int to, weight;
};

vector<Edge> graph[MAXN];
ll freq[MAXN];          // 每个站点的访问频率
ll subFreq[MAXN];       // 子树中的总访问频率
ll dpDown[MAXN];        // 以u为根的子树中所有目标节点到u的距离和
ll dpUp[MAXN];          // 以u为根时所有目标节点到u的距离和
ll totalFreq;           // 所有站点的总访问频率
int n, m;

void dfs1(int u, int parent) {
    subFreq[u] = freq[u];
    dpDown[u] = 0;
    for (const Edge& e : graph[u]) {
        int v = e.to, w = e.weight;
        if (v == parent) continue;
        dfs1(v, u);
        subFreq[u] += subFreq[v];
        dpDown[u] += dpDown[v] + subFreq[v] * w;
    }
}

void dfs2(int u, int parent) {
    for (const Edge& e : graph[u]) {
        int v = e.to, w = e.weight;
        if (v == parent) continue;
        // 换根：从u移动到v
        dpUp[v] = dpUp[u] + (totalFreq - 2 * subFreq[v]) * w;
        dfs2(v, u);
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        freq[i] = 0;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        graph[a].push_back({b, t});
        graph[b].push_back({a, t});
    }
    cin >> m;
    totalFreq = 0;
    for (int i = 0; i < m; i++) {
        int a, f;
        cin >> a >> f;
        freq[a] = f;
        totalFreq += f;
    }
    
    // 第一次DFS：以1为根
    dfs1(1, -1);
    // 初始化dpUp[1] = dpDown[1]
    dpUp[1] = dpDown[1];
    // 第二次DFS：换根
    dfs2(1, -1);
    
    // 找到最小总时间（往返距离 = 2 * 单程距离和）
    ll minTime = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        ll cur = 2 * dpUp[i];
        if (cur < minTime) minTime = cur;
    }
    cout << minTime << "\n";
    
    // 输出所有最优解的车站编号
    vector<int> ans;
    for (int i = 1; i <= n; i++)
        if (2 * dpUp[i] == minTime) ans.push_back(i);
    for (size_t i = 0; i < ans.size(); i++) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c;
    cin >> c;
    while (c--) solve();
    return 0;
}
