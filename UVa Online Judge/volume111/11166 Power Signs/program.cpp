// Power Signs
// UVa ID: 11166
// Verdict: Accepted
// Submission Date: 2025-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;

int main() {
    char s[MAXN];
    while (scanf("%s", s + 1) == 1 && s[1] != '0') {
        s[0] = '0';
        int n = strlen(s + 1);
        // 从低位向高位扫描（i从n到1）
        for (int i = n; i > 0; i--) {
            if (s[i] == '1') {
                int j = i - 1;
                // 向前寻找连续1的起始位置
                while (s[j] == '1') j--;
                // 检查连续1的长度
                // 连续1的长度≥2
                if (i - j >= 2) {
                    // 特殊情况：连续2个1且在最高位（j==0）
                    if (i - j == 2 && j == 0) s[i] = s[i - 1] = '+';
                    else {
                        // 一般情况：转换连续1
                        // 最后一个1变成-1
                        s[i] = '-';
                        // 中间的1变成0
                        for (int k = i - 1; k > j; k--) s[k] = '0';
                        // 进位（前面的0变成1），不变为+，因为有可能与前面的1构成更长的连续1串，
                        // 从而可以得到非0数字更少的表示，从而可能会更优
                        s[j] = '1';
                    }
                } else s[i] = '+';  // 单个1，直接变成+
            }
        }
        // 处理可能的最高位进位
        if (s[0] == '1') s[0] = '+';
        // 输出结果
        if (s[0] == '0') printf("%s\n", s + 1);
        else printf("%s\n", s);
    }
    return 0;
}
