// Sign of a Matrix
// UVa ID: 11671
// Verdict: Accepted
// Submission Date: 2026-04-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 205;

struct Edge {
    int to, weight;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, caseNum = 0;
    while (cin >> n && n != -1) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) cin >> grid[i];
        
        int total = 2 * n;
        vector<vector<Edge>> adj(total);
        
        // 根据符号建图
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int u = i;          // R[i]
                int v = n + j;      // -C[j]
                if (grid[i][j] == '+') 
                    adj[v].push_back({u, -1});  // -C[j] - R[i] <= -1
                else if (grid[i][j] == '-') 
                    adj[u].push_back({v, -1});  // R[i] - (-C[j]) <= -1
                else {  // '0'
                    adj[u].push_back({v, 0});   // R[i] - (-C[j]) <= 0
                    adj[v].push_back({u, 0});   // -C[j] - R[i] <= 0
                }
            }
        
        // SPFA 求最短路并检测负环
        vector<int> dist(total, 0);  // 所有点初始距离为 0
        vector<int> cnt(total, 0);
        vector<bool> inQueue(total, true);
        queue<int> q;
        
        for (int i = 0; i < total; ++i) q.push(i);
        
        bool hasNegCycle = false;
        while (!q.empty() && !hasNegCycle) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;
            
            for (const Edge& e : adj[u]) {
                int v = e.to;
                int w = e.weight;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if (cnt[v] >= total) {
                        hasNegCycle = true;
                        break;
                    }
                    if (!inQueue[v]) {
                        q.push(v);
                        inQueue[v] = true;
                    }
                }
            }
        }
        
        cout << "Case " << ++caseNum << ": ";
        if (hasNegCycle) {
            cout << -1 << "\n";
            continue;
        }
        
        // 计算最小操作次数：枚举平移量
        int ans = INF;
        for (int shift = -n; shift <= n; ++shift) {
            int sum = 0;
            for (int i = 0; i < n; ++i) 
                sum += abs(dist[i] + shift);           // R[i]
            for (int j = 0; j < n; ++j) 
                sum += abs(-dist[n + j] - shift);      // C[j] = -(-C[j]) 的相反数
            ans = min(ans, sum);
        }
        
        cout << ans << "\n";
    }
    return 0;
}
