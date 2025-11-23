// Animal Run
// UVa ID: 1376
// Verdict: Accepted
// Submission Date: 2025-11-22
// UVa Run Time: 0.650s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e6 + 9;
const ll INF = 1e18;

vector<pair<int, ll>> graph[N];

ll dijkstra(int s, int t) {
    vector<ll> dist(t + 1, INF);
    vector<bool> vis(t + 1, false);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, s});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        if (u == t) break;
        
        for (auto [v, w] : graph[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[t];
}

int n, m, s, t;

int getId(int i, int j, int half) {
    if (j < 0 || i >= n - 1) return s;
    if (i < 0 || j >= m - 1) return t;
    return i * m + j + n * m * half;
}

void addEdge(int u, int v, int w) {
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
}

void solve(int caseNum) {
    s = 2 * n * m + 1;
    t = s + 1;
    
    // 读入水平边
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            int w; cin >> w;
            addEdge(getId(i, j, 1), getId(i - 1, j, 0), w);
        }
    }
    
    // 读入垂直边
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            int w; cin >> w;
            addEdge(getId(i, j - 1, 1), getId(i, j, 0), w);
        }
    }
    
    // 读入对角边
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            int w; cin >> w;
            addEdge(getId(i, j, 0), getId(i, j, 1), w);
        }
    }
    
    ll result = dijkstra(s, t);
    cout << "Case " << caseNum << ": Minimum = " << result << endl;
    
    // 清理图
    for (int i = 0; i <= t; i++) graph[i].clear();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int caseNum = 1;
    while (cin >> n >> m && (n || m)) {
        solve(caseNum);
        caseNum++;
    }
    return 0;
}
