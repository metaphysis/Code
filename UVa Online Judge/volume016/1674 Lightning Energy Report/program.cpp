// Lightning Energy Report
// UVa ID: 1674
// Verdict: Accepted
// Submission Date: 2025-11-29
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
const int LOG = 16;

vector<int> graph[MAXN];
int depth[MAXN];
int parent[MAXN][LOG];
int diff[MAXN];
int result[MAXN];

void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    parent[u][0] = p;
    for (int i = 1; i < LOG; i++) 
        if (parent[u][i-1] != -1) 
            parent[u][i] = parent[parent[u][i-1]][i-1];
    
    for (int v : graph[u]) 
        if (v != p) 
            dfs(v, u);
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    int diffDepth = depth[u] - depth[v];
    for (int i = 0; i < LOG; i++) 
        if (diffDepth & (1 << i)) 
            u = parent[u][i];
    
    if (u == v) return u;
    
    for (int i = LOG - 1; i >= 0; i--) 
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    
    return parent[u][0];
}

void accumulate(int u, int p) {
    result[u] = diff[u];
    for (int v : graph[u]) 
        if (v != p) {
            accumulate(v, u);
            result[u] += result[v];
        }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    for (int caseNum = 1; caseNum <= t; caseNum++) {
        int n;
        cin >> n;
        
        // 初始化
        for (int i = 0; i < n; i++) {
            graph[i].clear();
            diff[i] = 0;
            result[i] = 0;
            for (int j = 0; j < LOG; j++) 
                parent[i][j] = -1;
        }
        
        // 建树
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        
        // 预处理LCA
        depth[0] = 0;
        dfs(0, -1);
        
        // 处理闪电
        int q;
        cin >> q;
        while (q--) {
            int a, b, c;
            cin >> a >> b >> c;
            int l = lca(a, b);
            
            diff[a] += c;
            diff[b] += c;
            diff[l] -= c;
            if (parent[l][0] != -1) 
                diff[parent[l][0]] -= c;
        }
        
        // 汇总结果
        accumulate(0, -1);
        
        // 输出结果
        cout << "Case #" << caseNum << ":\n";
        for (int i = 0; i < n; i++) 
            cout << result[i] << "\n";
    }
    
    return 0;
}
