// Project File Dependencies
// UVa ID: 1119
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int caseCount;
    cin >> caseCount; // 读取测试用例数量
    for (int caseIndex = 0; caseIndex < caseCount; ++caseIndex) {
        if (caseIndex > 0) cout << endl; // 测试用例之间输出空行
        int n, m;
        cin >> n >> m; // 读取任务数量和规则数量
        vector<vector<int>> graph(n + 1); // 邻接表，graph[i] 存储任务 i 依赖的所有任务
        vector<int> indegree(n + 1, 0);   // 入度数组
        // 读取每条规则
        for (int i = 0; i < m; ++i) {
            int target, k;
            cin >> target >> k;
            for (int j = 0; j < k; ++j) {
                int dep;
                cin >> dep;
                graph[dep].push_back(target); // 依赖指向目标：dep -> target
                indegree[target]++;
            }
        }
        // 最小堆，用于保证编号小的任务优先输出
        priority_queue<int, vector<int>, greater<int>> pq;
        // 将所有入度为 0 的任务加入堆
        for (int i = 1; i <= n; ++i)
            if (indegree[i] == 0) pq.push(i);
        vector<int> result;
        // 拓扑排序
        while (!pq.empty()) {
            int cur = pq.top();
            pq.pop();
            result.push_back(cur);
            // 遍历当前任务指向的所有目标任务
            for (int neighbor : graph[cur]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) pq.push(neighbor);
            }
        }
        // 输出结果
        for (size_t i = 0; i < result.size(); ++i) {
            if (i) cout << ' ';
            cout << result[i];
        }
        cout << '\n';
    }
    return 0;
}
