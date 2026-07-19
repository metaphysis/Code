// Fence the Vegetables Fail
// UVa ID: 13009
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.170s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Plant {
    long long x, y;
    int val;
};

struct Edge {
    long long x, yMin, yMax;
};

class Fenwick {
    vector<int> bit;
public:
    Fenwick(int n) { bit.assign(n + 2, 0); }
    void add(int idx, int delta) {
        for (; idx < (int)bit.size(); idx += idx & -idx) bit[idx] += delta;
    }
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) sum += bit[idx];
        return sum;
    }
    void rangeAdd(int l, int r, int delta) {
        if (l > r) return;
        add(l, delta);
        add(r + 1, -delta);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int P, V;
    while (cin >> P >> V) {
        vector<Plant> plants(P);
        vector<long long> ys;
        ys.reserve(P + 2 * V);
        long long totalVal = 0;
        for (int i = 0; i < P; ++i) {
            cin >> plants[i].x >> plants[i].y;
            plants[i].val = i + 1;
            totalVal += plants[i].val;
            ys.push_back(plants[i].y);
        }
        vector<pair<long long, long long>> vertices(V);
        for (int i = 0; i < V; ++i) cin >> vertices[i].first >> vertices[i].second;
        vector<Edge> edges;
        edges.reserve(V);
        // 提取垂直边，忽略水平边
        for (int i = 0; i < V; ++i) {
            int j = (i + 1) % V;
            long long x1 = vertices[i].first, y1 = vertices[i].second;
            long long x2 = vertices[j].first, y2 = vertices[j].second;
            if (x1 == x2) {
                long long yMin = min(y1, y2), yMax = max(y1, y2);
                edges.push_back({x1, yMin, yMax});
                ys.push_back(yMin);
                ys.push_back(yMax);
            }
        }
        // 离散化纵坐标
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        auto getIdx = [&](long long y) -> int {
            return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1; // 1-based
        };
        int n = ys.size();
        Fenwick bit(n + 2);
        // 按横坐标降序排序
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.x > b.x;
        });
        sort(plants.begin(), plants.end(), [](const Plant& a, const Plant& b) {
            return a.x > b.x;
        });
        int eIdx = 0;
        long long insideSum = 0;
        for (const Plant& plant : plants) {
            // 加入所有横坐标大于当前植物横坐标的垂直边
            while (eIdx < (int)edges.size() && edges[eIdx].x > plant.x) {
                const Edge& e = edges[eIdx];
                int l = getIdx(e.yMin);
                int r = getIdx(e.yMax) - 1; // 左闭右开 [yMin, yMax)
                if (l <= r) bit.rangeAdd(l, r, 1);
                ++eIdx;
            }
            int pos = getIdx(plant.y);
            int cnt = bit.query(pos);
            if (cnt & 1) insideSum += plant.val; // 奇数表示内部
        }
        long long ans = totalVal - insideSum;
        cout << ans << '\n';
    }
    return 0;
}
