// Strange Tax Calculation
// UVa ID: 11529
// Verdict: Accepted
// Submission Date: 2026-04-26
// UVa Run Time: 0.330s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    Point() {}
    Point(long long _x, long long _y) : x(_x), y(_y) {}
};

Point operator - (const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

long long cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

// 判断点所在的象限，用于极角排序
int quad(const Point& p) {
    if (p.x > 0 && p.y >= 0) return 1;
    if (p.x <= 0 && p.y > 0) return 2;
    if (p.x < 0 && p.y <= 0) return 3;
    return 4;
}

// 极角排序比较函数
bool angleCmp(const Point& a, const Point& b) {
    int qa = quad(a), qb = quad(b);
    if (qa != qb) return qa < qb;
    return cross(a, b) > 0;
}

int main() {
    int N, caseNo = 0;
    while (cin >> N, N) {
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) 
            cin >> pts[i].x >> pts[i].y;
        
        // 点数不足 3 时，没有 Bermuda block
        if (N < 3) {
            cout << fixed << setprecision(2);
            cout << "City " << ++caseNo << ": 0.00" << endl;
            continue;
        }
        
        long long totalInside = 0;  // 所有三角形内部点的总数 S
        
        for (int i = 0; i < N; ++i) {
            vector<Point> vec;
            // 以点 i 为原点，构造其他点的相对向量
            for (int j = 0; j < N; ++j) if (i != j) 
                vec.push_back(pts[j] - pts[i]);
            
            // 按极角排序
            sort(vec.begin(), vec.end(), angleCmp);
            int m = vec.size();
            // 复制一倍处理环形情况
            for (int j = 0; j < m; ++j) vec.push_back(vec[j]);
            
            long long bad = 0;  // 三点共半平面的三角形数 G(p)
            int k = 0;
            for (int j = 0; j < m; ++j) {
                if (k < j + 1) k = j + 1;
                // 找最远的 k 使得角度差严格小于 180°
                while (k < j + m && cross(vec[j], vec[k]) > 0) ++k;
                long long cnt = k - j - 1;
                if (cnt >= 2) bad += cnt * (cnt - 1) / 2;
            }
            // 注意：这里不需要除以 3，因为每个三角形只被其最小极角的顶点计数一次
            
            long long allTri = 1LL * m * (m - 1) * (m - 2) / 6;  // C(N-1, 3)
            long long good = allTri - bad;  // F(i)
            totalInside += good;
        }
        
        long long totalTriAll = 1LL * N * (N - 1) * (N - 2) / 6;  // C(N, 3)
        double ans = (double)totalInside / totalTriAll;
        
        cout << fixed << setprecision(2);
        cout << "City " << ++caseNo << ": " << ans << endl;
    }
    return 0;
}
