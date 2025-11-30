// Rectilinear Polygon
// UVa ID: 11106
// Verdict: Accepted
// Submission Date: 2025-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, id;
    Point(int x = 0, int y = 0, int id = 0) : x(x), y(y), id(id) {}
};

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) return;
        
        if (rank[rootA] < rank[rootB]) {
            parent[rootA] = rootB;
        } else if (rank[rootA] > rank[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rank[rootA]++;
        }
    }
    
    bool hasSingleComponent() {
        int root = find(0);
        for (int i = 1; i < parent.size(); i++) {
            if (find(i) != root) return false;
        }
        return true;
    }
};

bool solveTestCase() {
    int n;
    cin >> n;
    vector<Point> points(n);
    map<int, int> xCount, yCount;
    
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].id = i;
        xCount[points[i].x]++;
        yCount[points[i].y]++;
    }
    
    // 检查奇偶性条件
    for (auto& p : xCount) 
        if (p.second % 2 != 0) return false;
    for (auto& p : yCount) 
        if (p.second % 2 != 0) return false;
    
    // 按坐标分组构建边
    map<int, vector<int>> byY, byX;
    for (auto& p : points) {
        byY[p.y].push_back(p.id);
        byX[p.x].push_back(p.id);
    }
    
    UnionFind uf(n);
    long long perimeter = 0;
    
    // 构建水平边并连接端点
    for (auto& group : byY) {
        vector<int>& ids = group.second;
        // 按x坐标排序对应的点
        sort(ids.begin(), ids.end(), [&](int a, int b) {
            return points[a].x < points[b].x;
        });
        for (size_t i = 0; i < ids.size(); i += 2) {
            int id1 = ids[i], id2 = ids[i + 1];
            uf.unite(id1, id2);
            perimeter += (points[id2].x - points[id1].x);
        }
    }
    
    // 构建垂直边并连接端点
    for (auto& group : byX) {
        vector<int>& ids = group.second;
        // 按y坐标排序对应的点
        sort(ids.begin(), ids.end(), [&](int a, int b) {
            return points[a].y < points[b].y;
        });
        for (size_t i = 0; i < ids.size(); i += 2) {
            int id1 = ids[i], id2 = ids[i + 1];
            uf.unite(id1, id2);
            perimeter += (points[id2].y - points[id1].y);
        }
    }
    
    // 如果只有一个连通分量，则必定是简单多边形
    if (!uf.hasSingleComponent()) 
        return false;
    
    cout << perimeter << endl;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        if (!solveTestCase()) 
            cout << -1 << endl;
    }
    
    return 0;
}
