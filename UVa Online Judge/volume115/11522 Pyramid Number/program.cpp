// Pyramid Number
// UVa ID: 11522
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 小于78的严格金字塔数（打表）
const vector<int> strictPyramidUnder78 = {
    1, 11, 24, 30, 31, 32, 37, 38, 43, 45, 
    50, 52, 53, 54, 55, 57, 59, 60, 61, 62, 
    64, 65, 66, 67, 69, 71, 73, 74, 75, 76
};

// 统计不超过n的严格金字塔数个数
int countStrictPyramid(int n) {
    if (n <= 0) return 0;
    int count = 0;
    // 对于大于等于78的部分
    if (n >= 78) {
        count += n - 77;  // 78到n都是严格金字塔数
        n = 77;           // 只处理小于78的部分
    }
    // 统计小于78的严格金字塔数
    for (int x : strictPyramidUnder78) if (x <= n) count++;
    return count;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b;
        scanf("%d %d", &a, &b);
        // 确保a <= b
        if (a > b) swap(a, b);
        // 计算[a, b]区间内的严格金字塔数个数
        int result = countStrictPyramid(b) - countStrictPyramid(a - 1);
        printf("%d\n", result);
    }
    return 0;
}
