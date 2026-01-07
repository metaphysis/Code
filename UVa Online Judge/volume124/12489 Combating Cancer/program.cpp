// Combating Cancer
// UVa ID: 12489
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

class Tree {
private:
    vector<vector<int>> adj; // 邻接表
    int n; // 节点数
    vector<int> parent, depth, subtreeSize; // DFS 相关数组

    // DFS 计算父节点、深度和子树大小
    void dfs(int u, int p) {
        parent[u] = p;
        subtreeSize[u] = 1;
        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            subtreeSize[u] += subtreeSize[v];
        }
    }

    // 寻找树的所有重心
    vector<int> findCentroids() {
        dfs(1, -1); // 从节点1开始DFS，假设树是连通的
        vector<int> centroids;
        int minMax = n + 1; // 记录最小的最大子树大小
        
        for (int i = 1; i <= n; ++i) {
            int maxSubtree = n - subtreeSize[i]; // 考虑父节点方向的子树
            for (int v : adj[i]) {
                if (v == parent[i]) continue;
                maxSubtree = max(maxSubtree, subtreeSize[v]);
            }
            
            if (maxSubtree < minMax) {
                minMax = maxSubtree;
                centroids.clear();
                centroids.push_back(i);
            } else if (maxSubtree == minMax) {
                centroids.push_back(i);
            }
        }
        
        return centroids;
    }

    // 生成以 u 为根的子树 AHU 编码
    string encodeTree(int u, int parent) {
        vector<string> childrenCodes;
        for (int v : adj[u]) {
            if (v == parent) continue;
            childrenCodes.push_back(encodeTree(v, u));
        }
        
        // 排序是关键，确保结构相同的子树编码一致
        sort(childrenCodes.begin(), childrenCodes.end());
        
        string code = "(";
        for (const string& childCode : childrenCodes) {
            code += childCode;
        }
        code += ")";
        
        return code;
    }

public:
    Tree(int size) : n(size) {
        adj.resize(n + 1);
        parent.resize(n + 1);
        depth.resize(n + 1);
        subtreeSize.resize(n + 1);
    }

    // 从输入构建树
    void build() {
        for (int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    // 判断当前树是否与另一棵树同构
    bool isIsomorphicTo(Tree& other) {
        if (n != other.n) return false; // 节点数不同肯定不同构
        
        vector<int> centroids1 = findCentroids();
        vector<int> centroids2 = other.findCentroids();
        
        set<string> codes1;
        for (int root : centroids1) {
            string code = encodeTree(root, -1);
            codes1.insert(code);
        }
        
        for (int root : centroids2) {
            string code = other.encodeTree(root, -1);
            if (codes1.count(code)) {
                return true;
            }
        }
        
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        Tree tree1(N);
        Tree tree2(N);
        
        tree1.build();
        tree2.build();
        
        if (tree1.isIsomorphicTo(tree2)) cout << "S\n";
        else cout << "N\n";
    }
    
    return 0;
}
