// Rings n Ropes
// UVa ID: 10985
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.590s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = 1000000000;

int main() {
    int numCases;
    cin >> numCases;

    for (int caseIdx = 1; caseIdx <= numCases; ++caseIdx) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }

        vector<pair<int, int>> ropes;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            dist[a][b] = dist[b][a] = 1;
            ropes.push_back({a, b});
        }

        // Floyd-Warshall: 计算所有点对最短路径
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        int maxStretched = 0;

        // 遍历所有可能的 L 和 R
        for (int l = 0; l < n; ++l) {
            for (int r = l + 1; r < n; ++r) {
                if (dist[l][r] == INF) continue;

                int countStretched = 0;
                for (const auto& rope : ropes) {
                    int a = rope.first;
                    int b = rope.second;
                    
                    // 检查a和b是否都在L到R的某条最短路径上
                    // 并且它们处于不同的"侧"
                    if (dist[l][a] + dist[a][r] == dist[l][r] && 
                        dist[l][b] + dist[b][r] == dist[l][r]) {
                        // a和b都在最短路径上，检查是否在不同侧
                        if (dist[l][a] != dist[l][b]) {
                            countStretched++;
                        }
                    }
                }
                maxStretched = max(maxStretched, countStretched);
            }
        }

        cout << "Case #" << caseIdx << ": " << maxStretched << endl;
    }

    return 0;
}
