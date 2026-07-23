// Adventures in Moving Part V
// UVa ID: 10204
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int w, h, l, H;
    while (cin >> w >> h >> l >> H) {
        int dim[3];
        cin >> dim[0] >> dim[1] >> dim[2];
        sort(dim, dim + 3);
        bool ok = false;
        do {
            int a = dim[0]; // 宽度方向尺寸
            int b = dim[1]; // 高度方向尺寸
            int c = dim[2]; // 长度方向尺寸
            // 最终放置条件
            if (a <= w && b <= h && c <= l) {
                bool canPass = false;
                // 方式1：直接放入
                if (b <= H) canPass = true;
                // 方式2：前倾（绕宽轴旋转）
                if (!canPass && c <= H && b * c <= l * H && b * b + c * c <= h * h)
                    canPass = true;
                // 方式3：侧倾（绕长轴旋转）
                if (!canPass && a * a + b * b <= h * h) {
                    double d = sqrt((double)a * a + b * b);
                    double theta = atan2((double)a, (double)b) + acos((double)H / d);
                    if (a * cos(theta) + b * sin(theta) <= w + 1e-9)
                        canPass = true;
                }
                if (canPass) { ok = true; break; }
            }
        } while (next_permutation(dim, dim + 3));
        cout << (ok ? "The box goes on the truck." : "The box will not go on the truck.") << '\n';
    }
    return 0;
}
