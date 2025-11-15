// Dog Distance
// UVa ID: 11796
// Verdict: Accepted
// Submission Date: 2025-11-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

Point operator+(const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }
Point operator*(const Point& a, double t) { return Point(a.x * t, a.y * t); }
double dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
double length(const Point& a) { return sqrt(dot(a, a)); }
double dist(const Point& a, const Point& b) { return length(a - b); }

void solve() {
    int I;
    cin >> I;
    cout << fixed << setprecision(0);

    for (int cas = 1; cas <= I; cas++) {
        int A, B;
        cin >> A >> B;

        vector<Point> pathA(A), pathB(B);
        for (int i = 0; i < A; i++) cin >> pathA[i].x >> pathA[i].y;
        for (int i = 0; i < B; i++) cin >> pathB[i].x >> pathB[i].y;

        // 计算总长度和每段长度
        double lenA = 0, lenB = 0;
        vector<double> segLenA(A - 1), segLenB(B - 1);
        for (int i = 1; i < A; i++) {
            segLenA[i - 1] = dist(pathA[i - 1], pathA[i]);
            lenA += segLenA[i - 1];
        }
        for (int i = 1; i < B; i++) {
            segLenB[i - 1] = dist(pathB[i - 1], pathB[i]);
            lenB += segLenB[i - 1];
        }

        // 初始化状态
        int idxA = 0, idxB = 0;
        double posA = 0, posB = 0;
        Point curA = pathA[0], curB = pathB[0];
        double maxD = 0, minD = 1e9;

        // 初始距离
        maxD = max(maxD, dist(curA, curB));
        minD = min(minD, dist(curA, curB));

        while (idxA < A - 1 && idxB < B - 1) {
            // 当前线段向量和长度
            Point vecA = pathA[idxA + 1] - pathA[idxA];
            Point vecB = pathB[idxB + 1] - pathB[idxB];
            double lenSegA = segLenA[idxA];
            double lenSegB = segLenB[idxB];

            // 单位方向向量和速度向量
            Point dirA = vecA * (1.0 / lenSegA);
            Point dirB = vecB * (1.0 / lenSegB);
            Point velA = dirA * lenA;  // 速度向量
            Point velB = dirB * lenB;  // 速度向量

            // 剩余长度
            double remA = lenSegA - posA;
            double remB = lenSegB - posB;

            // 所需时间
            double tA = remA / lenA;
            double tB = remB / lenB;
            double dt = min(tA, tB);

            // 相对运动分析
            Point d0 = curA - curB;  // 初始相对位置
            Point dv = velA - velB;  // 相对速度
            
            double a = dot(dv, dv);
            double b = 2 * dot(d0, dv);
            double c = dot(d0, d0);

            // 检查的候选时间点
            vector<double> checkTimes = {0, dt};  // 端点
            
            // 检查顶点是否在区间内
            if (fabs(a) > 1e-12) {
                double t_vertex = -b / (2 * a);
                if (t_vertex > 1e-9 && t_vertex < dt - 1e-9) {
                    checkTimes.push_back(t_vertex);
                }
            }

            // 计算各候选点的距离
            for (double t : checkTimes) {
                Point pA = curA + velA * t;
                Point pB = curB + velB * t;
                double d = dist(pA, pB);
                maxD = max(maxD, d);
                minD = min(minD, d);
            }

            // 更新状态
            curA = curA + velA * dt;
            curB = curB + velB * dt;
            posA += dt * lenA;
            posB += dt * lenB;

            // 检查是否到达线段终点
            if (fabs(posA - lenSegA) < 1e-9) {
                idxA++;
                posA = 0;
            }
            if (fabs(posB - lenSegB) < 1e-9) {
                idxB++;
                posB = 0;
            }
        }

        // 最终位置的距离
        double finalD = dist(curA, curB);
        maxD = max(maxD, finalD);
        minD = min(minD, finalD);

        int ans = static_cast<int>(maxD - minD + 0.5);
        cout << "Case " << cas << ": " << ans << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
