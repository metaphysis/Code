// Biometrics
// UVa ID: 10556
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    int cross(const Point& p) const { return x * p.y - y * p.x; }
    int dot(const Point& p) const { return x * p.x + y * p.y; }
    int distSq() const { return x * x + y * y; }
};

bool areSimilar(const vector<Point>& p1, const vector<Point>& p2) {
    int n = p1.size();
    // 检查边长比例是否恒定
    long long scaleNum = -1, scaleDen = -1;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        Point vec1 = p1[j] - p1[i], vec2 = p2[j] - p2[i];
        long long lenSq1 = vec1.distSq(), lenSq2 = vec2.distSq();
        // 初始化比例
        if (scaleNum == -1) scaleNum = lenSq2, scaleDen = lenSq1;
        else {
            // 检查比例是否一致: lenSq2/lenSq1 == scaleNum/scaleDen
            if (lenSq2 * scaleDen != lenSq1 * scaleNum) return false;
        }
    }
    // 检查角度关系（转向）
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n, k = (i + 2) % n;
        Point vec1a = p1[j] - p1[i], vec1b = p1[k] - p1[j];
        Point vec2a = p2[j] - p2[i], vec2b = p2[k] - p2[j];
        int cross1 = vec1a.cross(vec1b), cross2 = vec2a.cross(vec2b);
        // 转向必须相同（不允许反射）
        if ((cross1 > 0) != (cross2 > 0)) return false;
        // 可选：更精确的角度检查，不加本题也能通过
        int dot1 = vec1a.dot(vec1b), dot2 = vec2a.dot(vec2b);
        if ((long long)cross1 * dot2 != (long long)cross2 * dot1) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int f;
    while (cin >> f && f != 0) {
        vector<Point> poly1(f), poly2(f);
        for (int i = 0; i < f; i++) cin >> poly1[i].x >> poly1[i].y;
        for (int i = 0; i < f; i++) cin >> poly2[i].x >> poly2[i].y;
        if (areSimilar(poly1, poly2)) cout << "similar\n";
        else cout << "dissimilar\n";
    }
    return 0;
}
