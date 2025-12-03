// Frosting on the Cake
// UVa ID: 13291
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<long long> sumA(3, 0), sumB(3, 0);
        
        // 读入 A，注意 i 从 1 开始，所以取模时用 i%3 正好对应题目中的 i%3
        for (int i = 1; i <= n; ++i) {
            long long val;
            cin >> val;
            sumA[i % 3] += val;
        }
        
        // 读入 B
        for (int i = 1; i <= n; ++i) {
            long long val;
            cin >> val;
            sumB[i % 3] += val;
        }
        
        // 计算三种颜色的总面积
        long long color0 = sumA[0] * sumB[0] + sumA[1] * sumB[2] + sumA[2] * sumB[1];
        long long color1 = sumA[0] * sumB[1] + sumA[1] * sumB[0] + sumA[2] * sumB[2];
        long long color2 = sumA[0] * sumB[2] + sumA[1] * sumB[1] + sumA[2] * sumB[0];
        
        // 输出结果
        cout << color0 << " " << color1 << " " << color2 << "\n";
    }
    return 0;
}
