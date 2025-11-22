// The Integer All-time Champ
// UVa ID: 10248
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

string solve(int l, int r) {
    // 图
    vector<vector<int>> g(10, vector<int>(10, 0));
    // 顶点度以及顶点是否出现
    vector<int> d(10, 0), visited(10, 0);
    // 构建图（只对两位数）
    for (int i = l; i <= r; i++) {
        // 单个数字不建边，可能已被包含
        if (i < 10) continue;
        int x = i / 10, y = i % 10;
        g[x][y]++, d[x]++, d[y]--;
        visited[x] = visited[y] = 1;
     }
    // 根据有向欧拉路径的充要条件平衡度数
    vector<int> outNodes, inNodes;
    for (int i = 0; i < 10; i++) {
        int cnt = abs(d[i]);
        if (d[i] > 0) while (cnt--) outNodes.push_back(i);
        if (d[i] < 0) while (cnt--) inNodes.push_back(i);
    }
    // 任意选择出度为正和出度为负的顶点之间建边，总平衡度不变
    while (outNodes.size() > 1 && inNodes.size() > 1) {
        int from = inNodes.back(); inNodes.pop_back();
        int to = outNodes.back(); outNodes.pop_back();
        g[from][to]++;
    }
    string result;
    // 确定可能的欧拉路径起点
    vector<int> start;
    if (outNodes.size()) start.push_back(outNodes[0]);
    for (int i = 0; i < 10; i++)
        if (visited[i])
            start.push_back(i);
    // 找欧拉路径，Hierholzer算法
    function<void(int, vector<int>&)> dfs = [&](int u, vector<int>& path) {
        for (int v = 0; v < 10; v++) {
            while (g[u][v] > 0) {
                g[u][v]--;
                dfs(v, path);
                path.push_back(v);
            }
        }
    };
    for (auto s : start) {
        vector<int> path;
        dfs(s, path);
        // 从此顶点开始的欧拉路径可能为空，也就是说之前的遍历中边已经覆盖过
        if (path.empty()) continue;
        path.push_back(s);
        reverse(path.begin(), path.end());
        for (int node : path) result += to_string(node);
    }
    // 添加未被包含的单个数字
    for (int i = l; i <= r; i++)
        if (i < 10 && !visited[i])
            result += to_string(i);
    return result;
}

int main() {
    int m, n;
    while (cin >> m >> n) cout << solve(m, n) << '\n';
    return 0;
}
