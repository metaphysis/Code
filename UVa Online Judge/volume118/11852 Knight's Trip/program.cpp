// Knight's Trip
// UVa ID: 11852
// Verdict: Accepted
// Submission Date: 2026-06-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算骑士从 (0,0) 到 (x,y) 的最少步数
int minKnightMoves(int x, int y) {
    int a = max(abs(x), abs(y)); // 较大坐标
    int b = min(abs(x), abs(y)); // 较小坐标
    // 两个特殊点，公式不适用
    if (a == 1 && b == 0) return 3;
    if (a == 2 && b == 2) return 4;
    // 下界取较大值
    int d = max((a + 1) / 2, (a + b + 2) / 3);
    // 调整奇偶性，使步数与 (a+b) 同奇偶
    if ((d + a + b) % 2 != 0) ++d;
    return d;
}

int main() {
    string token;
    while (cin >> token) {
        if (token == "END") break;
        int x = stoi(token);
        int y;
        cin >> y;
        cout << minKnightMoves(x, y) << '\n';
    }
    return 0;
}
