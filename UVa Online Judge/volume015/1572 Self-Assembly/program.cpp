// Self-Assembly
// UVa ID: 1572
// Verdict: Accepted
// Submission Date: 2025-10-21
// UVa Run Time: 0.140s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int NODES = 52; // A+ = 0, A- = 1, B+ = 2, B- = 3, ... Z+ = 50, Z- = 51

// 将字符标签转换为节点索引
int charToIndex(char letter, char sign) {
    int base = (letter - 'A') * 2;
    if (sign == '+') return base;
    else return base + 1;
}

// 获取相反符号的节点索引（利用异或操作）
int opposite(int idx) {
    return idx ^ 1; // 0<->1, 2<->3, ...
}

// 检测有向图中是否存在环
bool hasCycle(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> visited(n, 0); // 0=未访问, 1=在栈中, 2=已完成
    bool cycle = false;
    // 使用function包装递归lambda函数
    function<void(int)> dfs = [&](int u) {
        visited[u] = 1;
        for (int v : graph[u]) {
            if (visited[v] == 0) {
                dfs(v);
            } else if (visited[v] == 1) {
                cycle = true;
            }
            if (cycle) return;
        }
        visited[u] = 2;
    };
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            dfs(i);
            if (cycle) return true;
        }
    }
    return false;
}

int main() {
    int n;
    while (cin >> n) {
        vector<vector<int>> graph(NODES);
        for (int i = 0; i < n; i++) {
            string mol;
            cin >> mol;
            // 分子长度为8字符，4个两字符标签
            int edges[4];
            for (int j = 0; j < 4; j++) {
                string label = mol.substr(j * 2, 2);
                if (label == "00") {
                    edges[j] = -1;
                } else {
                    edges[j] = charToIndex(label[0], label[1]);
                }
            }
            // 对分子上的每条非-1边，与其他非-1边建立 opposite(e) -> f
            for (int j = 0; j < 4; j++) {
                if (edges[j] == -1) continue;
                for (int k = 0; k < 4; k++) {
                    if (k == j || edges[k] == -1) continue;
                    graph[opposite(edges[j])].push_back(edges[k]);
                }
            }
        }
        if (hasCycle(graph)) {
            cout << "unbounded" << endl;
        } else {
            cout << "bounded" << endl;
        }
    }
    return 0;
}
