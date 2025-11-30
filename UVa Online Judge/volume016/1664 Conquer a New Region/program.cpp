// Conquer a New Region
// UVa ID: 1664
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.200s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;

// 并查集数据结构
struct DSU {
    int parent[MAXN];
    long long size[MAXN];  // 连通分量的大小
    long long sum[MAXN];   // 连通分量的总容量
    
    void init(int n) {
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
            sum[i] = 0;
        }
    }
    
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
};

struct Edge {
    int u, v, cap;
    bool operator<(const Edge& other) const {
        return cap > other.cap;  // 按容量降序排序
    }
};

Edge edges[MAXN];
DSU dsu;

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        // 读取所有边
        for (int i = 0; i < n - 1; i++) 
            scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].cap);
        
        // 初始化并查集
        dsu.init(n);
        
        // 按容量降序排序边
        sort(edges, edges + n - 1);
        
        // 处理每条边
        for (int i = 0; i < n - 1; i++) {
            int u = edges[i].u, v = edges[i].v, cap = edges[i].cap;
            int rootU = dsu.find(u);
            int rootV = dsu.find(v);
            
            // 计算两个连通分量作为新中心的总容量
            long long sumU = dsu.sum[rootU] + dsu.size[rootV] * cap;
            long long sumV = dsu.sum[rootV] + dsu.size[rootU] * cap;
            
            // 合并连通分量，选择总容量更大的作为新值
            if (sumU > sumV) {
                dsu.parent[rootV] = rootU;
                dsu.size[rootU] += dsu.size[rootV];
                dsu.sum[rootU] = sumU;
            } else {
                dsu.parent[rootU] = rootV;
                dsu.size[rootV] += dsu.size[rootU];
                dsu.sum[rootV] = sumV;
            }
        }
        
        // 最终答案在唯一的连通分量的sum中
        int root = dsu.find(1);
        printf("%lld\n", dsu.sum[root]);
    }
    return 0;
}
