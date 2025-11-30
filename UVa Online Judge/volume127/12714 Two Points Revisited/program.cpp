// Two Points Revisited
// UVa ID: 12714
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (y1 > y2) { swap(x1, x2); swap(y1, y2); }
        long long dx = x2 - x1, dy = y2 - y1;
        long long newX1, newY1, newX2, newY2;
        if (dx == 0) {
            // 原直线垂直，新直线水平
            newX1 = 0; newY1 = y1;
            newX2 = 1; newY2 = y1;
        } else if (dy == 0) {
            // 原直线水平，新直线垂直
            newX1 = x1; newY1 = 0;
            newX2 = x1; newY2 = 1;
        } else {
            // 一般情况：使用向量 (dy, -dx)
            long long g = __gcd(abs(dx), abs(dy));
            dx /= g, dy /= g;
            if (dx > 0) {
                newX1 = 0; newY1 = abs(dx);
                newX2 = abs(dy); newY2 = 0;
            } else {
                newX1 = 0; newY1 = 0;
                newX2 = abs(dy); newY2 = abs(dx);
            }
        }
        cout << "Case " << cs << ": " << newX1 << " " << newY1 << " " << newX2 << " " << newY2 << endl;
    }
    return 0;
}
