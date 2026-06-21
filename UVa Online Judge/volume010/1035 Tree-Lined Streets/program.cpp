// Tree-Lined Streets
// UVa ID: 1035
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct Point {
    double x, y;
};

struct Street {
    Point p1, p2;
    double length;
    vector<double> interPos; // 交点到p1的距离
};

// 叉积
double cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

// 向量减法
Point sub(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

// 计算两点距离
double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 判断两条线段是否相交，若相交返回true，并计算在第一线段上的参数t（0<t<1）
bool intersectSegment(const Street& s1, const Street& s2, double& t) {
    Point d1 = {s1.p2.x - s1.p1.x, s1.p2.y - s1.p1.y};
    Point d2 = {s2.p2.x - s2.p1.x, s2.p2.y - s2.p1.y};
    double denom = cross(d1, d2);
    if (fabs(denom) < eps) return false; // 平行
    Point diff = {s2.p1.x - s1.p1.x, s2.p1.y - s1.p1.y};
    t = cross(diff, d2) / denom;
    double u = cross(diff, d1) / denom;
    // 交点必须在两线段内部（不在端点）
    if (t > eps && t < 1.0 - eps && u > eps && u < 1.0 - eps)
        return true;
    return false;
}

// 计算一条街道上的最大种树数
int maxTreesOnStreet(const Street& st) {
    vector<double> pos = st.interPos;
    sort(pos.begin(), pos.end());
    double L = st.length;
    int cnt = 0;
    if (pos.empty()) {
        // 没有交叉点，整条街道都可种
        if (L > eps) cnt += (int)(L / 50.0) + 1;
        return cnt;
    }
    // 左端到第一个交叉点
    if (pos[0] > 25.0 + eps) {
        double len = pos[0] - 25.0;
        if (len > eps) cnt += (int)(len / 50.0) + 1;
    }
    // 相邻交叉点之间
    for (size_t i = 0; i + 1 < pos.size(); ++i) {
        double gap = pos[i + 1] - pos[i];
        if (gap > 50.0 + eps) {
            double len = gap - 50.0;
            if (len > eps) cnt += (int)(len / 50.0) + 1;
        }
    }
    // 最后一个交叉点到右端
    if (L - pos.back() > 25.0 + eps) {
        double len = L - pos.back() - 25.0;
        if (len > eps) cnt += (int)(len / 50.0) + 1;
    }
    return cnt;
}

int main() {
    int n;
    int mapNo = 0;
    while (cin >> n && n) {
        ++mapNo;
        vector<Street> streets(n);
        for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            streets[i].p1 = {(double)x1, (double)y1};
            streets[i].p2 = {(double)x2, (double)y2};
            streets[i].length = dist(streets[i].p1, streets[i].p2);
        }
        // 计算所有交点
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                double t;
                if (intersectSegment(streets[i], streets[j], t)) {
                    double posI = t * streets[i].length;
                    streets[i].interPos.push_back(posI);
                    // 需要计算交点在第二条街道上的位置，即参数u
                    // 但我们可以通过交点坐标和第二条街道的起点计算
                    Point inter = {streets[i].p1.x + t * (streets[i].p2.x - streets[i].p1.x),
                                   streets[i].p1.y + t * (streets[i].p2.y - streets[i].p1.y)};
                    double posJ = dist(streets[j].p1, inter);
                    streets[j].interPos.push_back(posJ);
                }
            }
        int total = 0;
        for (int i = 0; i < n; ++i)
            total += maxTreesOnStreet(streets[i]);
        cout << "Map " << mapNo << '\n';
        cout << "Trees = " << total << "\n";
    }
    return 0;
}
