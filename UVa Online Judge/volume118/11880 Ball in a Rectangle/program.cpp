// Ball in a Rectangle
// UVa ID: 11880
// Verdict: Accepted
// Submission Date: 2026-01-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

double normalize(double pos, double length) {
    // 将pos映射到[0, 2*length]内
    pos = fmod(pos, 2 * length);
    if (pos < 0) pos += 2 * length;
    // 对称映射到[0, length]
    if (pos > length) pos = 2 * length - pos;
    return pos;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(2);

    int L, W, R, a, v, s;
    double x, y;
    while (cin >> L >> W >> x >> y >> R >> a >> v >> s) {
        if (L == 0 && W == 0 && x == 0 && y == 0 && R == 0 && a == 0 && v == 0 && s == 0) break;

        double rad = a * PI / 180.0;
        double dx = v * cos(rad);
        double dy = v * sin(rad);

        // 有效运动区域
        double Lx = L - 2 * R;
        double Ly = W - 2 * R;

        // 无界空间中的位置
        double tx = x - R + dx * s;
        double ty = y - R + dy * s;

        // 映射回有效区域
        double px = normalize(tx, Lx);
        double py = normalize(ty, Ly);

        // 加回半径偏移
        double finalX = px + R;
        double finalY = py + R;

        cout << finalX << " " << finalY << "\n";
    }
    return 0;
}
