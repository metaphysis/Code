// Can't be too GREEDY
// UVa ID: 10471
// Verdict: Accepted
// Submission Date: 2025-11-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void generateTestCase(int k) {
    vector<pair<int, int>> edges;
    vector<int> vertexColor; // 顶点编号 -> 颜色
    vector<vector<int>> colorVertices(k + 1); // 颜色 -> 顶点列表
    
    int nextVertexId = 1;
    
    // 使用BFS构造树
    queue<pair<int, int>> q; // (顶点编号, 颜色)
    
    // 从根节点开始，颜色为k
    int root = nextVertexId++;
    vertexColor.push_back(0); // 0-index填充
    vertexColor.push_back(k);
    colorVertices[k].push_back(root);
    q.push({root, k});
    
    while (!q.empty()) {
        auto [currentId, currentColor] = q.front();
        q.pop();
        
        // 如果当前颜色为1，不需要生成子节点
        if (currentColor == 1) continue;
        
        // 为当前节点生成子节点，颜色分别为1, 2, ..., currentColor-1
        for (int childColor = 1; childColor < currentColor; childColor++) {
            int childId = nextVertexId++;
            vertexColor.push_back(childColor);
            colorVertices[childColor].push_back(childId);
            
            // 添加边
            edges.push_back({currentId, childId});
            
            // 如果子节点颜色大于1，继续处理
            if (childColor > 1)
                q.push({childId, childColor});
        }
    }
    
    int n = nextVertexId - 1;
    int m = edges.size();
    
    // 构建顶点顺序：按颜色从低到高排列
    vector<int> order;
    for (int color = 1; color <= k; color++)
        for (int vertexId : colorVertices[color])
            order.push_back(vertexId);
    
    // 输出结果
    cout << n << " " << m << "\n";
    for (auto& e : edges)
        cout << e.first << " " << e.second << "\n";
    
    for (size_t i = 0; i < order.size(); i++) {
        if (i > 0) cout << " ";
        cout << order[i];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k;
    while (cin >> k)
        generateTestCase(k);
    
    return 0;
}
