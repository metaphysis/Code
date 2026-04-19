// Points Polygons and Containers
// UVa ID: 881
// Verdict: Accepted
// Submission Date: 2026-02-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

struct Polygon {
    int id;
    vector<Point> vertices;
};

// 浮点数比较
inline int sgn(double x) {
    if (fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;
}

// 叉积
double cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 射线法判断点是否在多边形内
bool pointInPolygon(const Point &p, const Polygon &poly) {
    int n = poly.vertices.size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        Point a = poly.vertices[i];
        Point b = poly.vertices[j];
        // 射线法：从点向右发射水平射线
        if ((sgn(a.y - p.y) > 0) != (sgn(b.y - p.y) > 0)) {
            double x = a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y);
            if (sgn(x - p.x) > 0) cnt++;
        }
    }
    return cnt % 2 == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseNum = 0; caseNum < t; caseNum++) {
        if (caseNum > 0) cout << "\n";
        int nc;
        cin >> nc;
        vector<Polygon> polygons(nc);
        map<int, int> idToIdx;
        // 读取多边形
        for (int i = 0; i < nc; i++) {
            int id;
            cin >> id;
            polygons[i].id = id;
            idToIdx[id] = i;
            double x, y;
            while (cin.peek() != '\n' && cin.peek() != EOF) {
                cin >> x >> y;
                polygons[i].vertices.emplace_back(x, y);
            }
        }
        int np;
        cin >> np;
        vector<pair<int, Point>> points(np);
        // 读取点
        for (int i = 0; i < np; i++) {
            int id;
            double x, y;
            cin >> id >> x >> y;
            points[i] = {id, Point(x, y)};
        }

        // 1. 找出所有多边形之间的包含关系
        // contains[i][j] = true 表示多边形i包含多边形j
        vector<vector<bool>> contains(nc, vector<bool>(nc, false));
        for (int i = 0; i < nc; i++)
            for (int j = 0; j < nc; j++) {
                if (i == j) continue;
                // 检查多边形j是否在多边形i内
                bool allInside = true;
                for (const Point &p : polygons[j].vertices)
                    if (!pointInPolygon(p, polygons[i])) {
                        allInside = false;
                        break;
                    }
                if (allInside) contains[i][j] = true;
            }
        // 2. 对每个点，找出所有包含它的多边形
        vector<pair<int, int>> results;
        for (const auto &[pid, p] : points) {
            set<int> containingPolys;
            for (int i = 0; i < nc; i++)
                if (pointInPolygon(p, polygons[i]))
                    containingPolys.insert(i);
            // 3. 找出最内层的多边形（移除所有外层多边形）
            set<int> removed;
            for (int i : containingPolys)
                for (int j : containingPolys)
                    if (i != j && contains[j][i])
                        removed.insert(j);  // j是外层的，移除
            for (auto r : removed) containingPolys.erase(r);
            int container = 0;
            if (containingPolys.size()) container = polygons[*containingPolys.begin()].id;
            results.emplace_back(pid, container);
        }
        // 按点ID排序输出
        sort(results.begin(), results.end());
        for (const auto &[pid, cid] : results) 
            cout << pid << " " << cid << "\n";
    }
    return 0;
}
