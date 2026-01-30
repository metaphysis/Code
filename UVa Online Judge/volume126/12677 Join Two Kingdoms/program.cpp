// Join Two Kingdoms
// UVa ID: 12677
// Verdict: Accepted
// Submission Date: 2026-01-22
// UVa Run Time: 0.760s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40005;

vector<int> adjA[MAXN], adjB[MAXN];
int dist1[MAXN], dist2[MAXN];
int depthA[MAXN], depthB[MAXN];
int n, m;

void bfs(int start, vector<int> adj[], int dist[], int n) {
    for (int i = 1; i <= n; ++i) dist[i] = -1;
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (dist[v] == -1) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}

void computeEccentricity(vector<int> adj[], int n, int ecc[]) {
    // 第一次 BFS 找直径一端
    bfs(1, adj, dist1, n);
    int far = 1;
    for (int i = 2; i <= n; ++i) if (dist1[i] > dist1[far]) far = i;
    // 第二次 BFS 从 far 出发，得到 dist1 为到 far 的距离
    bfs(far, adj, dist1, n);
    // 找直径另一端
    int far2 = far;
    for (int i = 1; i <= n; ++i) if (dist1[i] > dist1[far2]) far2 = i;
    // 第三次 BFS 从 far2 出发，得到 dist2 为到 far2 的距离
    bfs(far2, adj, dist2, n);
    // 偏心率 = max(dist1, dist2)
    for (int i = 1; i <= n; ++i) ecc[i] = max(dist1[i], dist2[i]);
}

int main() {
    while (cin >> n >> m) {
        // 清空邻接表
        for (int i = 1; i <= n; ++i) adjA[i].clear();
        for (int i = 1; i <= m; ++i) adjB[i].clear();
        // 读入树 A
        for (int i = 0; i < n - 1; ++i) {
            int a, b; cin >> a >> b;
            adjA[a].push_back(b);
            adjA[b].push_back(a);
        }
        // 读入树 B
        for (int i = 0; i < m - 1; ++i) {
            int c, d; cin >> c >> d;
            adjB[c].push_back(d);
            adjB[d].push_back(c);
        }
        // 计算偏心率
        computeEccentricity(adjA, n, depthA);
        computeEccentricity(adjB, m, depthB);
        // 计算原直径
        int da = *max_element(depthA + 1, depthA + n + 1);
        int db = *max_element(depthB + 1, depthB + m + 1);
        int T = max(da, db);
        // 对 depthB 排序并计算前缀和
        sort(depthB + 1, depthB + m + 1);
        vector<long long> prefixSum(m + 2, 0);
        for (int i = 1; i <= m; ++i) prefixSum[i] = prefixSum[i - 1] + depthB[i];
        long long total = 0;
        int c = T - 1;  // 偏移量
        for (int i = 1; i <= n; ++i) {
            int x = depthA[i];
            // 找到第一个 > c - x 的位置
            int pos = upper_bound(depthB + 1, depthB + m + 1, c - x) - depthB;
            int cnt = m - pos + 1;
            long long sum = prefixSum[m] - prefixSum[pos - 1];
            total += (long long)(m - cnt) * T;  // 贡献为 T 的部分
            total += sum + (long long)cnt * (x + 1);  // 贡献为 x + b + 1 的部分
        }
        double ans = (double)total / (n * m);
        printf("%.3lf\n", ans);
    }
    return 0;
}
