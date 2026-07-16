// The Story of Two Coins
// UVa ID: 10834
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

// 将角度归一化到 [0, 2*PI)
double normAngle(double th) {
    while (th < 0) th += 2 * PI;
    while (th >= 2 * PI) th -= 2 * PI;
    return th;
}

int main() {
    int R, r;
    double x, y;
    int caseNo = 0;
    while (cin >> R >> r >> x >> y) {
        if (R == 0 && r == 0) break;
        ++caseNo;
        double a = R + r;               // 圆心轨迹半径
        double d = hypot(x, y);         // |T|
        // 计算 c = O·T
        double c = (a * a + d * d - r * r) / 2.0;
        double p = c / d;               // O 在 T 方向上的投影长度
        double h2 = a * a - p * p;
        if (h2 < -1e-12) {              // 无解
            cout << "Case " << caseNo << ":\n";
            cout << "IMPOSSIBLE\n";
            continue;
        }
        double h = sqrt(max(0.0, h2));
        double ux = x / d, uy = y / d;
        double vx = -uy, vy = ux;       // 垂直单位向量
        // 两个圆心
        double Ox1 = p * ux + h * vx, Oy1 = p * uy + h * vy;
        double Ox2 = p * ux - h * vx, Oy2 = p * uy - h * vy;
        // 对应的角度
        double theta1 = normAngle(atan2(Oy1, Ox1));
        double theta2 = normAngle(atan2(Oy2, Ox2));
        // 按时间顺序（角度升序）排列
        if (theta1 > theta2) {
            swap(theta1, theta2);
            swap(Ox1, Ox2);
            swap(Oy1, Oy2);
        }
        double ratio = a / r;           // (R+r)/r
        // 计算P
        auto calcP = [&](double theta, double Ox, double Oy) {
            double alpha = PI / 2.0 + ratio * theta;
            double Px = Ox + r * cos(alpha);
            double Py = Oy + r * sin(alpha);
            return make_pair(Px, Py);
        };
        auto p1 = calcP(theta1, Ox1, Oy1);
        auto p2 = calcP(theta2, Ox2, Oy2);
        cout << "Case " << caseNo << ":\n";
        cout << fixed << setprecision(3) << p1.first << " " << p1.second << "\n";
        cout << fixed << setprecision(3) << p2.first << " " << p2.second << "\n";
    }
    return 0;
}
