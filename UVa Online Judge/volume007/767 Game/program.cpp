// Game
// UVa ID: 767
// Verdict: Accepted
// Submission Date: 2026-07-04
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = -1;

// BFS 返回最小步数，若不可达返回 -1
int bfs(int N, int L, int K, int Q, const vector<int>& circleColor, const vector<vector<pair<int,int>>>& adj) {
    vector<vector<int>> dist(N + 1, vector<int>(N + 1, -1));
    queue<pair<int,int>> q;
    dist[L][K] = 0;
    q.push({L, K});
    
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        int u = cur.first, v = cur.second;
        int d = dist[u][v];
        
        // 移动第一个棋子 u
        for (auto &e : adj[u]) {
            int nxt = e.first, col = e.second;
            if (col == circleColor[v] && nxt != v) {
                if (nxt == Q) return d + 1;
                if (dist[nxt][v] == -1) {
                    dist[nxt][v] = d + 1;
                    q.push({nxt, v});
                }
            }
        }
        
        // 移动第二个棋子 v
        for (auto &e : adj[v]) {
            int nxt = e.first, col = e.second;
            if (col == circleColor[u] && nxt != u) {
                if (nxt == Q) return d + 1;
                if (dist[u][nxt] == -1) {
                    dist[u][nxt] = d + 1;
                    q.push({u, nxt});
                }
            }
        }
    }
    return -1;
}

int main() {
    int numDatasets;
    cin >> numDatasets;
    bool firstCase = true;
    
    for (int caseIdx = 0; caseIdx < numDatasets; ++caseIdx) {
        int N, L, K, Q;
        cin >> N >> L >> K >> Q;
        
        vector<int> circleColor(N + 1);
        for (int i = 1; i <= N; ++i) cin >> circleColor[i];
        
        int M;
        cin >> M;
        vector<vector<pair<int,int>>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int A, B, C;
            cin >> A >> B >> C;
            adj[A].push_back({B, C});
        }
        
        int ans = bfs(N, L, K, Q, circleColor, adj);
        
        // 输出，数据集间空行
        if (!firstCase) cout << "\n";
        firstCase = false;
        
        if (ans == -1) {
            cout << "NO\n";
        } else {
            cout << "YES\n" << ans << "\n";
        }
    }
    
    return 0;
}
