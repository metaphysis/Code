// Graph and Queries
// UVa ID: 1479
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.870s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;
const int MAXM = 60005;

int n, m;
int weight[MAXN];
int u[MAXM], v[MAXM];
bool deleted[MAXM];
vector<tuple<char, int, int>> operations;
int parent[MAXN];
vector<int> trees[MAXN];
int queryCount;
long long querySum;

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    
    if (trees[a].size() < trees[b].size()) swap(a, b);
    
    // 归并两个有序数组
    vector<int> merged;
    merged.reserve(trees[a].size() + trees[b].size());
    int i = 0, j = 0;
    while (i < trees[a].size() && j < trees[b].size()) {
        if (trees[a][i] < trees[b][j]) 
            merged.push_back(trees[a][i++]);
        else 
            merged.push_back(trees[b][j++]);
    }
    while (i < trees[a].size()) merged.push_back(trees[a][i++]);
    while (j < trees[b].size()) merged.push_back(trees[b][j++]);
    
    trees[a] = move(merged);
    trees[b].clear();
    parent[b] = a;
}

int query(int x, int k) {
    x = find(x);
    if (k < 1 || k > trees[x].size()) return 0;
    return trees[x][trees[x].size() - k];  // 直接O(1)访问
}

void change(int x, int newVal) {
    int root = find(x);
    
    // 二分查找旧值并删除
    auto& vec = trees[root];
    auto it = lower_bound(vec.begin(), vec.end(), weight[x]);
    vec.erase(it);
    
    // 插入新值
    weight[x] = newVal;
    it = lower_bound(vec.begin(), vec.end(), newVal);
    vec.insert(it, newVal);
}

int main() {
    int caseNum = 1;
    while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
        for (int i = 1; i <= n; i++) scanf("%d", &weight[i]);
        for (int i = 1; i <= m; i++) scanf("%d%d", &u[i], &v[i]);
        
        memset(deleted, 0, sizeof(deleted));
        operations.clear();
        char op;
        while (scanf(" %c", &op) && op != 'E') {
            if (op == 'D') {
                int x; scanf("%d", &x);
                deleted[x] = true;
                operations.emplace_back('D', x, 0);
            } else if (op == 'Q') {
                int x, k; scanf("%d%d", &x, &k);
                operations.emplace_back('Q', x, k);
            } else if (op == 'C') {
                int x, v; scanf("%d%d", &x, &v);
                operations.emplace_back('C', x, weight[x]);
                weight[x] = v;
            }
        }
        
        // 初始化
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            trees[i] = {weight[i]};
        }
        
        // 构建初始图（不包括被删除的边）
        for (int i = 1; i <= m; i++) 
            if (!deleted[i]) merge(u[i], v[i]);
        
        queryCount = 0;
        querySum = 0;
        
        // 倒序处理操作
        for (int i = operations.size() - 1; i >= 0; i--) {
            char op = get<0>(operations[i]);
            int x = get<1>(operations[i]);
            int y = get<2>(operations[i]);
            
            if (op == 'D') merge(u[x], v[x]);
            else if (op == 'Q') {
                queryCount++;
                querySum += query(x, y);
            }
            else if (op == 'C') change(x, y);
        }
        
        double average = queryCount ? (double)querySum / queryCount : 0.0;
        printf("Case %d: %.6f\n", caseNum++, average);
    }
    return 0;
}
