// Polylops
// UVa ID: 10575
// Verdict: Accepted
// Submission Date: 2025-11-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point operator - (const Point& other) const { return Point(x - other.x, y - other.y); }
    Point operator + (const Point& other) const { return Point(x + other.x, y + other.y); }
    bool operator == (const Point& other) const { return x == other.x && y == other.y; }
};

typedef Point Vector;

// 点积
int dot(const Vector& v1, const Vector& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

// 检查两条线段是否垂直
bool isPerpendicular(const Vector& v1, const Vector& v2) {
    return dot(v1, v2) == 0;
}

// 检查点 c 是否在线段 s 的垂直平分线上
bool isOnPerpendicularBisector(const Point& p1, const Point& p2, const Point& c) {
    Point mid((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
    Vector v1 = p2 - p1, v2 = c - mid;
    return isPerpendicular(v1, v2);
}

// 检查 n 为奇数时的对称轴（边中点到顶点的连线）
bool checkOddSymmetry(const vector<Point>& poly, int i, int j, int k) {
    int n = poly.size();
    // 检查顶点是否在边的垂直平分线上
    if (!isOnPerpendicularBisector(poly[i], poly[j], poly[k])) return false;
    // 检查两侧对应点
    Point axisMid((poly[i].x + poly[j].x) / 2, (poly[i].y + poly[j].y) / 2);
    int left = (i - 1 + n) % n, right = (j + 1) % n;
    while (left != k && right != k) {
        if (!isOnPerpendicularBisector(poly[left], poly[right], poly[k])) return false;
        if (!isOnPerpendicularBisector(poly[left], poly[right], axisMid)) return false;
        left = (left - 1 + n) % n, right = (right + 1) % n;
        if (left == right) break;
    }
    return true;
}

// 检查 n 为偶数时过两个顶点的对称轴
bool checkEvenVertexAxis(const vector<Point>& poly, int i, int j) {
    int n = poly.size();
    for (int k = 1; k < n / 2; k++) {
        int ii = (i + k) % n, jj = (i - k + n) % n;
        if (ii == j || jj == j) continue;
        if (!isOnPerpendicularBisector(poly[ii], poly[jj], poly[i])) return false;
        if (!isOnPerpendicularBisector(poly[ii], poly[jj], poly[j])) return false;
    }
    return true;
}

// 检查 n 为偶数时过边中点的对称轴
bool checkEvenEdgeAxis(const vector<Point>& poly, int i, int j) {
    int n = poly.size();
    Point mid((poly[i].x + poly[j].x) / 2, (poly[i].y + poly[j].y) / 2);
    Point axisDir = poly[j] - poly[i];
    // 检查两侧对应点
    int left = (j + 1) % n, right = (i - 1 + n) % n;
    int steps = (n - 2) / 2;
    while (steps) {
        Point leftRightMid((poly[left].x + poly[right].x) / 2, (poly[left].y + poly[right].y) / 2);
        Vector toMid = leftRightMid - mid;
        if (!isPerpendicular(axisDir, toMid)) return false;
        left = (left + 1) % n, right = (right - 1 + n) % n;
        steps--;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNum = 1;
    while (cin >> n && n != 0) {
        vector<Point> polygon(n);
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            polygon[i] = Point(2 * x, 2 * y); // 坐标乘以2避免小数
        }
        int symmetryCount = 0;
        if (n % 2 == 1) {
            // 奇数情况：检查每条边和对应的顶点
            for (int i = 0; i < n; i++) {
                int j = (i + 1) % n;
                int k = (i + 1 + n / 2) % n; // 对应的顶点
                if (checkOddSymmetry(polygon, i, j, k)) symmetryCount++;
            }
        } else {
            // 偶数情况：检查过顶点的对称轴
            int half = n / 2;
            for (int i = 0; i < half; i++) {
                int j = i + half;
                if (checkEvenVertexAxis(polygon, i, j)) symmetryCount++;
            }
            // 偶数情况：检查过边中点的对称轴
            for (int i = 0; i < half; i++) {
                int j = i + 1;
                if (checkEvenEdgeAxis(polygon, i, j)) symmetryCount++;
            }
        }
        cout << "Polygon #" << caseNum << " has " << symmetryCount << " symmetry line(s)." << endl;
        caseNum++;
    }
    return 0;
}
