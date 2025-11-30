// Rankings
// UVa ID: 12263
// Verdict: Accepted
// Submission Date: 2025-11-29
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

vector<int> topologicalSort(int n, vector<vector<int>>& graph, vector<int>& indegree) {
    vector<int> result;
    queue<int> q;
    
    // 找到所有入度为0的节点
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    bool multiple = false;  // 是否有多个选择
    
    while (!q.empty()) {
        if (q.size() > 1) {
            multiple = true;  // 有多个节点可选，结果不确定
        }
        
        int current = q.front();
        q.pop();
        result.push_back(current);
        
        // 更新相邻节点的入度
        for (int neighbor : graph[current]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    // 如果结果数量不等于n，说明有环
    if (result.size() != n) {
        return vector<int>();  // 返回空向量表示不可能
    }
    
    // 如果有多个选择，标记为不确定
    if (multiple) {
        return vector<int>(n, -1);  // 用-1表示不确定
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        int n;
        cin >> n;
        
        vector<int> lastYear(n);
        for (int i = 0; i < n; i++) {
            cin >> lastYear[i];
        }
        
        // 构建去年的排名关系矩阵
        vector<vector<bool>> lastYearOrder(n + 1, vector<bool>(n + 1, false));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                lastYearOrder[lastYear[i]][lastYear[j]] = true;
            }
        }
        
        int m;
        cin >> m;
        
        // 初始化今年的关系矩阵（开始时与去年相同）
        vector<vector<bool>> thisYearOrder = lastYearOrder;
        
        // 处理变化的关系
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            // 交换a和b的关系
            swap(thisYearOrder[a][b], thisYearOrder[b][a]);
        }
        
        // 构建图
        vector<vector<int>> graph(n + 1);
        vector<int> indegree(n + 1, 0);
        
        // 根据今年的关系构建有向图
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && thisYearOrder[i][j]) {
                    graph[i].push_back(j);
                    indegree[j]++;
                }
            }
        }
        
        // 进行拓扑排序
        vector<int> result = topologicalSort(n, graph, indegree);
        
        if (result.empty()) {
            // 存在环，不可能
            cout << "IMPOSSIBLE\n";
        } else if (result[0] == -1) {
            // 结果不确定
            for (int i = 0; i < n; i++) {
                if (i > 0) cout << " ";
                cout << "?";
            }
            cout << "\n";
        } else {
            // 确定的结果
            for (int i = 0; i < n; i++) {
                if (i > 0) cout << " ";
                cout << result[i];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
