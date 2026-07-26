// Summits 
// UVa ID: 12130
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.140s
// https://blog.csdn.net/metaphysis/article/details/163173959

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int r, c, id;
    long long h;
};

struct Query {
    long long T;
    int id;
    long long h;
};

struct DSU {
    vector<int> parent, rank;
    vector<long long> maxH;

    DSU(int n, const vector<long long>& height) {
        parent.resize(n);
        rank.assign(n, 0);
        maxH = height;
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (rank[ra] < rank[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) ++rank[ra];
        if (maxH[rb] > maxH[ra]) maxH[ra] = maxH[rb];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int rows, cols;
        long long d;
        cin >> rows >> cols >> d;
        int N = rows * cols;
        vector<long long> height(N);
        vector<Point> points(N);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                long long h;
                cin >> h;
                int id = r * cols + c;
                height[id] = h;
                points[id] = {r, c, id, h};
            }
        }
        // 按高度降序排序，用于逐步加入并查集
        sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
            return a.h > b.h;
        });
        // 生成查询，按阈值 T = h - d 降序排序
        vector<Query> queries(N);
        for (int i = 0; i < N; ++i) {
            queries[i] = {height[i] - d, i, height[i]};
        }
        sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
            return a.T > b.T;
        });
        DSU dsu(N, height);
        vector<char> active(N, 0);
        int ptr = 0;          // 指向 points 中下一个待加入的点
        long long ans = 0;
        for (const auto& q : queries) {
            long long T = q.T;
            // 加入所有高度 > T 的点
            while (ptr < N && points[ptr].h > T) {
                int id = points[ptr].id;
                active[id] = 1;
                int r = id / cols, c = id % cols;
                if (r > 0) { int nid = id - cols; if (active[nid]) dsu.unite(id, nid); }
                if (r < rows - 1) { int nid = id + cols; if (active[nid]) dsu.unite(id, nid); }
                if (c > 0) { int nid = id - 1; if (active[nid]) dsu.unite(id, nid); }
                if (c < cols - 1) { int nid = id + 1; if (active[nid]) dsu.unite(id, nid); }
                ++ptr;
            }
            // 查询当前点所在连通分量的最大高度
            int root = dsu.find(q.id);
            if (dsu.maxH[root] <= q.h) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}
