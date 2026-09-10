// City Park
// UVa ID: 12882
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.410s

#include <bits/stdc++.h>
using namespace std;

struct Rect { long long x, y, w, h; long long area; };
struct VEdge { long long x, y1, y2; int id; };
struct HEdge { long long y, x1, x2; int id; };

class DSU {
public:
    vector<int> parent, rank;
    DSU(int n) { parent.resize(n); rank.resize(n, 0); for (int i = 0; i < n; ++i) parent[i] = i; }
    int find(int x) { if (parent[x] != x) parent[x] = find(parent[x]); return parent[x]; }
    void unite(int a, int b) { int ra = find(a), rb = find(b); if (ra == rb) return; if (rank[ra] < rank[rb]) swap(ra, rb); parent[rb] = ra; if (rank[ra] == rank[rb]) ++rank[ra]; }
};

// 处理同一 x 坐标下的所有竖边，合并重叠的 y 区间对应的矩形
void processVEdges(vector<VEdge>& edges, DSU& dsu) {
    if (edges.empty()) return;
    sort(edges.begin(), edges.end(), [](const VEdge& a, const VEdge& b) {
        if (a.y1 != b.y1) return a.y1 < b.y1;
        return a.y2 < b.y2;
    });
    multiset<pair<long long, int>> active; // {右端点, 矩形id}
    for (auto& e : edges) {
        long long l = e.y1;
        auto it = active.lower_bound({l, -1});
        while (it != active.end()) {
            int id2 = it->second;
            dsu.unite(e.id, id2);
            ++it;
        }
        active.insert({e.y2, e.id});
    }
}

// 处理同一 y 坐标下的所有横边，合并重叠的 x 区间对应的矩形
void processHEdges(vector<HEdge>& edges, DSU& dsu) {
    if (edges.empty()) return;
    sort(edges.begin(), edges.end(), [](const HEdge& a, const HEdge& b) {
        if (a.x1 != b.x1) return a.x1 < b.x1;
        return a.x2 < b.x2;
    });
    multiset<pair<long long, int>> active; // {右端点, 矩形id}
    for (auto& e : edges) {
        long long l = e.x1;
        auto it = active.lower_bound({l, -1});
        while (it != active.end()) {
            int id2 = it->second;
            dsu.unite(e.id, id2);
            ++it;
        }
        active.insert({e.x2, e.id});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    while (cin >> N) {
        vector<Rect> rects(N);
        map<long long, vector<VEdge>> vGroups;
        map<long long, vector<HEdge>> hGroups;
        for (int i = 0; i < N; ++i) {
            long long X, Y, W, H;
            cin >> X >> Y >> W >> H;
            rects[i] = {X, Y, W, H, W * H};
            // 竖边：左边界和右边界
            vGroups[X].push_back({X, Y, Y + H, i});
            vGroups[X + W].push_back({X + W, Y, Y + H, i});
            // 横边：下边界和上边界
            hGroups[Y].push_back({Y, X, X + W, i});
            hGroups[Y + H].push_back({Y + H, X, X + W, i});
        }
        DSU dsu(N);
        for (auto& kv : vGroups) processVEdges(kv.second, dsu);
        for (auto& kv : hGroups) processHEdges(kv.second, dsu);
        vector<long long> totalArea(N, 0);
        for (int i = 0; i < N; ++i) {
            int root = dsu.find(i);
            totalArea[root] += rects[i].area;
        }
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            if (dsu.find(i) == i) ans = max(ans, totalArea[i]);
        }
        cout << ans << "\n";
    }
    return 0;
}
