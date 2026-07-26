// Drawing Polygon
// UVa ID: 13045
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163219970

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    const double PI = acos(-1.0);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        double L, x, y;
        cin >> N >> L >> x >> y;
        if (caseNo > 1) cout << "\n";
        cout << "Case #" << caseNo << ":\n";
        double half = PI / N;                     // 半中心角
        double delta = 2.0 * PI / N;              // 中心角步长
        double h = (L / 2.0) * (cos(half) / sin(half)); // 边心距（下边到中心的垂直距离）
        double cx = x + L / 2.0;                  // 中心横坐标
        double cy = y + h;                        // 中心纵坐标
        double R = L / (2.0 * sin(half));         // 外接圆半径
        double dx0 = -L / 2.0;                    // P0相对中心的x分量
        double dy0 = -h;                          // P0相对中心的y分量
        double baseAngle = atan2(dy0, dx0);       // P0的极角
        for (int i = 0; i < N; ++i) {
            double angle = baseAngle + i * delta;
            double px = cx + R * cos(angle);
            double py = cy + R * sin(angle);
            if (i == 0) { px = x; py = y; }       // 确保第一个点与输入完全一致
            cout << fixed << setprecision(6) << px << " " << py << "\n";
        }
    }
    return 0;
}
