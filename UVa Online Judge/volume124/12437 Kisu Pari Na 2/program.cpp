// Kisu Pari Na 2
// UVa ID: 12437
// Verdict: Accepted
// Submission Date: 2026-04-26
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int INF = 1e9;

vector<int> adj[MAXN];
bool vis[MAXN];
int farNode, maxDist;

void dfs(int u, int p, int dist, int& far, int& maxD) {
    vis[u] = true;
    if (dist > maxD) {
        maxD = dist;
        far = u;
    }
    for (int v : adj[u]) if (v != p) {
        dfs(v, u, dist + 1, far, maxD);
    }
}

// 返回树的直径（边数）
int getDiameter(int root) {
    maxDist = -1;
    dfs(root, -1, 0, farNode, maxDist);
    maxDist = -1;
    dfs(farNode, -1, 0, farNode, maxDist);
    return maxDist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N, M;
        cin >> N >> M;
        
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
            vis[i] = false;
        }
        
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        // best[k] 表示覆盖至少 k 个节点的最小花费
        vector<int> best(N + 1, INF);
        
        for (int i = 1; i <= N; ++i) {
            if (!vis[i]) {
                // 先求直径
                int diam = getDiameter(i);
                // 再统计这棵树的节点数
                queue<int> q;
                q.push(i);
                vector<bool> localVis(N + 1, false);
                localVis[i] = true;
                int sz = 0;
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    sz++;
                    for (int v : adj[u]) if (!localVis[v]) {
                        localVis[v] = true;
                        q.push(v);
                    }
                }
                // 对于这棵树，计算覆盖 k 个节点的最小花费
                for (int k = 1; k <= sz; ++k) {
                    int cost;
                    if (k <= diam + 1)
                        cost = k - 1;
                    else
                        cost = 2 * k - diam - 2;
                    if (cost < best[k])
                        best[k] = cost;
                }
            }
        }
        
        int q;
        cin >> q;
        cout << "Case " << caseNo << ":\n";
        while (q--) {
            int K;
            cin >> K;
            if (K > N || best[K] == INF)
                cout << "impossible\n";
            else
                cout << best[K] << "\n";
        }
    }
    return 0;
}
