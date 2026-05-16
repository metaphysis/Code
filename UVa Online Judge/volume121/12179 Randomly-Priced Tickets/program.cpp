// Randomly-Priced Tickets
// UVa ID: 12179
// Verdict: Accepted
// Submission Date: 2026-05-05
// UVa Run Time: 0.410s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;        // 最大城镇数
const int MAXM = 10005;      // 最大预算 + 边界
const int INF = 1e9;         // 无穷大

int main() {
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int N, R;
        cin >> N >> R;
        
        // 读入邻接矩阵
        vector<string> graph(N);
        for (int i = 0; i < N; ++i) cin >> graph[i];
        
        // ---------- Floyd-Warshall 求最少乘车次数 ----------
        vector<vector<int>> dist(N, vector<int>(N, INF));
        for (int i = 0; i < N; ++i) {
            dist[i][i] = 0;
            for (int j = 0; j < N; ++j) {
                if (graph[i][j] == 'Y') dist[i][j] = 1;
            }
        }
        
        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        
        // ---------- 概率预处理 ----------
        int maxK = N - 1;   // 最多需要 maxK 次乘车
        // dp[i][s] = i次乘车总费用恰好为s的概率
        vector<vector<double>> dp(maxK + 1, vector<double>(MAXM, 0.0));
        // prob[i][s] = i次乘车总费用 <= s 的概率
        vector<vector<double>> prob(maxK + 1, vector<double>(MAXM, 0.0));
        
        dp[0][0] = 1.0;
        
        // 动态规划计算恰好概率
        for (int i = 1; i <= maxK; ++i) {
            for (int s = 1; s < MAXM; ++s) {
                double sum = 0.0;
                for (int x = 1; x <= R; ++x) {
                    if (s - x >= 0) sum += dp[i - 1][s - x];
                }
                dp[i][s] = sum / R;
            }
        }
        
        // 累积得到 <= 概率
        for (int i = 1; i <= maxK; ++i) {
            double cum = 0.0;
            for (int s = 1; s < MAXM; ++s) {
                cum += dp[i][s];
                prob[i][s] = cum;
            }
        }
        
        // ---------- 回答查询 ----------
        int C;
        cin >> C;
        cout << "Case " << caseNum << "\n";
        for (int q = 0; q < C; ++q) {
            int a, b, m;
            cin >> a >> b >> m;
            --a; --b;
            int k = dist[a][b];
            double r = (m >= MAXM - 1) ? 1.0 : prob[k][m];
            cout << fixed << setprecision(6) << r << "\n";
        }
        cout << "\n";
    }
    return 0;
}
