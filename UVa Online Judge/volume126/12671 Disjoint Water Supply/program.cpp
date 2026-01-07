// Disjoint Water Supply
// UVa ID: 12671
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1005;

vector<int> graph[MAXC];  // 有向图
vector<int> pred[MAXC];   // 前驱
int idom[MAXC];           // 最近支配点
vector<int> domTree[MAXC]; // 支配树

// 快速计算最近支配点
void computeDominators(int C) {
    // 初始化
    for (int i = 1; i <= C; i++) {
        idom[i] = -1;
        domTree[i].clear();
    }
    idom[1] = 0; // 1 的支配点是 0（表示没有支配点或根）
    
    // 按拓扑序处理（编号顺序就是拓扑序）
    for (int v = 2; v <= C; v++) {
        if (pred[v].empty()) {
            idom[v] = 1;
            continue;
        }
        
        // 找所有前驱的公共最近支配点
        int common = pred[v][0];
        for (size_t i = 1; i < pred[v].size(); i++) {
            int a = common, b = pred[v][i];
            // 找 a 和 b 在支配树中的 LCA
            while (a != b) {
                if (a > b) a = idom[a];
                else b = idom[b];
            }
            common = a;
        }
        idom[v] = common;
    }
    
    // 构建支配树
    for (int i = 1; i <= C; i++) {
        if (idom[i] > 0) {
            domTree[idom[i]].push_back(i);
        }
    }
}

// DFS 标记子树
void dfsMark(int u, int root, vector<int>& mark) {
    mark[u] = root;
    for (int v : domTree[u]) {
        dfsMark(v, root, mark);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int C, P;
    while (cin >> C >> P) {
        // 初始化
        for (int i = 1; i <= C; i++) {
            graph[i].clear();
            pred[i].clear();
        }
        
        // 读入图
        for (int i = 0; i < P; i++) {
            int U, V;
            cin >> U >> V;
            graph[U].push_back(V);
            pred[V].push_back(U);
        }
        
        // 计算支配点
        computeDominators(C);
        
        // 方法：对于支配树中 1 的每个直接子节点，标记它的整个子树
        // 如果两个节点在不同的子树中，或者一个是 1，那么它们就是 disjoint 的
        
        vector<int> subtreeRoot(C + 1, 0);
        
        // 标记每个节点的子树
        for (int child : domTree[1]) {
            dfsMark(child, child, subtreeRoot);
        }
        // 1 本身标记为 0
        subtreeRoot[1] = 0;
        
        // 计算答案
        int count = 0;
        
        // 1 与所有其他城市
        count += (C - 1);
        
        // 其他城市对
        for (int i = 2; i <= C; i++) {
            for (int j = i + 1; j <= C; j++) {
                // 如果 i 和 j 在不同的子树中，或者至少有一个是 1 的直接子节点且另一个不在同一子树
                if (subtreeRoot[i] != subtreeRoot[j]) {
                    count++;
                }
            }
        }
        
        cout << count << endl;
    }
    return 0;
}
