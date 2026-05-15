// Classifying Lots in a Subdivision
// UVa ID: 223
// Verdict: Accepted
// Submission Date: 2026-05-15
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    bool operator<(const Point& o) const { return x != o.x ? x < o.x : y < o.y; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, cas = 0;
    while (cin >> n && n) {
        vector<pair<Point, Point>> segs(n);
        map<Point, int> id;
        vector<Point> pts;
        
        for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Point p1(x1, y1), p2(x2, y2);
            segs[i] = {p1, p2};
            if (!id.count(p1)) id[p1] = pts.size(), pts.push_back(p1);
            if (!id.count(p2)) id[p2] = pts.size(), pts.push_back(p2);
        }
        
        // 计算矩形边界
        int minX = 10001, maxX = 0, minY = 10001, maxY = 0;
        for (size_t i = 0; i < pts.size(); ++i) {
            minX = min(minX, pts[i].x); maxX = max(maxX, pts[i].x);
            minY = min(minY, pts[i].y); maxY = max(maxY, pts[i].y);
        }
        
        int tot = pts.size();
        vector<vector<pair<int, int>>> g(tot);
        for (int i = 0; i < n; ++i) {
            int u = id[segs[i].first], v = id[segs[i].second];
            g[u].push_back({v, i});
            g[v].push_back({u, i});
        }
        
        // 每个顶点的邻接边按极角逆时针排序
        for (int i = 0; i < tot; ++i) {
            sort(g[i].begin(), g[i].end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
                Point pa = pts[a.first], pb = pts[b.first], cur = pts[i];
                return atan2(pa.y - cur.y, pa.x - cur.x) < atan2(pb.y - cur.y, pb.x - cur.x);
            });
        }
        
        // 标记有向边是否已使用
        map<tuple<int, int, int>, bool> used;
        // 存储每个面的信息：(边数, 边列表)
        vector<pair<int, vector<int>>> faces;
        
        // 遍历所有有向边
        for (int u = 0; u < tot; ++u) {
            for (size_t j = 0; j < g[u].size(); ++j) {
                int v = g[u][j].first, e = g[u][j].second;
                if (used[{u, v, e}]) continue;
                
                vector<int> es;
                int cu = u, cv = v, ce = e;
                do {
                    used[{cu, cv, ce}] = true;
                    es.push_back(ce);
                    // 在 cv 点找到进入边的位置
                    size_t idx = 0;
                    while (g[cv][idx].first != cu) ++idx;
                    // 取逆时针方向的下一条边
                    size_t ni = (idx + 1) % g[cv].size();
                    int nv = g[cv][ni].first, ne = g[cv][ni].second;
                    cu = cv; cv = nv; ce = ne;
                } while (!(cu == u && cv == v && ce == e));
                
                if (es.size() >= 3) faces.push_back({(int)es.size(), es});
            }
        }
        
        // 找出外表面（包含矩形边界上的边）
        int outer = -1;
        for (size_t i = 0; i < faces.size() && outer == -1; ++i) {
            for (size_t j = 0; j < faces[i].second.size(); ++j) {
                int e = faces[i].second[j];
                Point p1 = segs[e].first, p2 = segs[e].second;
                if (p1.x == minX || p1.x == maxX || p1.y == minY || p1.y == maxY ||
                    p2.x == minX || p2.x == maxX || p2.y == minY || p2.y == maxY) {
                    outer = i; break;
                }
            }
        }
        
        // 统计内表面（地块）
        map<int, int> cnt;
        if (faces.size() == 1) cnt[faces[0].first] = 1;
        else for (size_t i = 0; i < faces.size(); ++i) if ((int)i != outer) cnt[faces[i].first]++;
        
        // 输出
        if (++cas > 1) cout << '\n';
        cout << "Case " << cas << '\n';
        int total = 0;
        for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
            total += it->second;
            cout << "Number of lots with perimeter consisting of " << it->first
                 << " surveyor's lines = " << it->second << '\n';
        }
        cout << "Total number of lots = " << total << '\n';
    }
    return 0;
}
