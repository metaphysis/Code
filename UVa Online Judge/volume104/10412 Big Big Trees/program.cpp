// Big Big Trees
// UVa ID: 10412
// Verdict: Accepted
// Submission Date: 2025-12-07
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// 计算叉积 (p1-p0) × (p2-p0)
long long cross(const Point& p0, const Point& p1, const Point& p2) {
    return (long long)(p1.x - p0.x) * (p2.y - p0.y) - (long long)(p1.y - p0.y) * (p2.x - p0.x);
}

// 快速排斥实验：检查两个线段 bounding box 是否相交
bool boundingBoxOverlap(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    return max(a1.x, a2.x) >= min(b1.x, b2.x) &&
           max(b1.x, b2.x) >= min(a1.x, a2.x) &&
           max(a1.y, a2.y) >= min(b1.y, b2.y) &&
           max(b1.y, b2.y) >= min(a1.y, a2.y);
}

// 检查点是否在线段上（包括端点）
bool onSegment(const Point& p, const Point& a, const Point& b) {
    // 先检查 bounding box
    if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x) ||
        p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) {
        return false;
    }
    // 叉积为0表示三点共线
    return cross(a, b, p) == 0;
}

// 检查线段A1A2是否与线段B1B2相交（包括端点在另一线段上）
bool segmentsIntersect(const Point& A1, const Point& A2, const Point& B1, const Point& B2) {
    // 快速排斥实验
    if (!boundingBoxOverlap(A1, A2, B1, B2)) return false;
    long long c1 = cross(A1, A2, B1);
    long long c2 = cross(A1, A2, B2);
    long long c3 = cross(B1, B2, A1);
    long long c4 = cross(B1, B2, A2);
    // 跨立试验：如果两个叉积异号，则线段相交
    if (c1 * c2 < 0 && c3 * c4 < 0) return true;
    // 检查端点是否在另一线段上
    if (c1 == 0 && onSegment(B1, A1, A2)) return true;
    if (c2 == 0 && onSegment(B2, A1, A2)) return true;
    if (c3 == 0 && onSegment(A1, B1, B2)) return true;
    if (c4 == 0 && onSegment(A2, B1, B2)) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n, m, k; cin >> n >> m >> k;
        vector<vector<int>> leaf(n + 1);
        vector<int> h(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> h[i];
            leaf[i].resize(h[i] + 1);
            leaf[i][0] = 0;
            for (int j = 1; j <= h[i]; j++) cin >> leaf[i][j];
        }
        int totalWalk = 0;
        // 处理每一对相邻的树
        for (int i = 1; i < n; i++) {
            int treePos1 = (i - 1) * m;
            int treePos2 = i * m;
            int minDist = INT_MAX;
            // 枚举左侧树起跳高度和右侧树着陆高度
            for (int a = 1; a <= h[i]; a++) {
                // 起跳点：左侧树叶子的右端点
                Point A(treePos1 + leaf[i][a], a);
                for (int b = 1; b <= h[i + 1]; b++) {
                    // 着陆点：右侧树叶子的左端点
                    Point B(treePos2 - leaf[i + 1][b], b);
                    // 检查跳跃距离（平方）
                    long long dx = B.x - A.x;
                    long long dy = B.y - A.y;
                    long long distSq = dx * dx + dy * dy;
                    if (distSq > (long long)k * k) continue;
                    bool valid = true;
                    // 检查与左侧树其他叶子的相交
                    for (int height = 1; height <= h[i]; height++) {
                        if (height == a) continue; // 跳过起跳叶子
                        // 叶子的两个端点
                        Point leafLeft(treePos1 - leaf[i][height], height);
                        Point leafRight(treePos1 + leaf[i][height], height);
                        // 检查跳跃线段是否与叶子线段相交
                        if (segmentsIntersect(A, B, leafLeft, leafRight)) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) continue;
                    // 检查与右侧树其他叶子的相交
                    for (int height = 1; height <= h[i + 1]; height++) {
                        if (height == b) continue; // 跳过着陆叶子
                        Point leafLeft(treePos2 - leaf[i + 1][height], height);
                        Point leafRight(treePos2 + leaf[i + 1][height], height);
                        if (segmentsIntersect(A, B, leafLeft, leafRight)) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) continue;
                    // 计算行走距离
                    int walkDist = leaf[i][a] + leaf[i + 1][b];
                    minDist = min(minDist, walkDist);
                }
            }
            // 若无法跳跃，可以直接走地面。WTF！
            if (minDist == INT_MAX) minDist = m;
            totalWalk += minDist;
        }
        cout << totalWalk << endl;
    }
    return 0;
}
