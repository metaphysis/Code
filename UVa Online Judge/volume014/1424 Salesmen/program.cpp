// Salesmen
// UVa ID: 1424
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_VERTICES = 105;
const int MAX_PATH_LENGTH = 205;
const int INF = 0x3f3f3f3f;

bool graph[MAX_VERTICES][MAX_VERTICES];
int dp[MAX_PATH_LENGTH][MAX_VERTICES];
vector<int> path;

int main() {
    int testCases;
    cin >> testCases;
    while (testCases--) {
        int numVertices, numEdges;
        cin >> numVertices >> numEdges;
        
        memset(graph, false, sizeof(graph));
        for (int i = 1; i <= numVertices; i++) {
            graph[i][i] = true; // 同一个顶点是相邻的
        }
        
        for (int i = 0; i < numEdges; i++) {
            int u, v;
            cin >> u >> v;
            graph[u][v] = graph[v][u] = true;
        }
        
        int pathLength;
        cin >> pathLength;
        path.resize(pathLength + 1);
        for (int i = 1; i <= pathLength; i++) {
            cin >> path[i];
        }
        
        memset(dp, INF, sizeof(dp));
        
        // 初始化第一个位置
        for (int v = 1; v <= numVertices; v++) {
            dp[1][v] = (path[1] == v ? 0 : 1);
        }
        
        // 动态规划
        for (int i = 2; i <= pathLength; i++) {
            for (int v = 1; v <= numVertices; v++) {
                for (int u = 1; u <= numVertices; u++) {
                    if (graph[u][v]) {
                        dp[i][v] = min(dp[i][v], dp[i - 1][u] + (path[i] == v ? 0 : 1));
                    }
                }
            }
        }
        
        int minDistance = INF;
        for (int v = 1; v <= numVertices; v++) {
            minDistance = min(minDistance, dp[pathLength][v]);
        }
        
        cout << minDistance << endl;
    }
    return 0;
}
