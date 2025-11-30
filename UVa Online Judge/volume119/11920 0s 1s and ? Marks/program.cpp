// 0s 1s and ? Marks
// UVa ID: 11920
// Verdict: Accepted
// Submission Date: 2025-11-30
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
char s[MAXN], segmentType[MAXN];
int segmentLength[MAXN];

int main() {
    int testCases, caseNumber = 0;
    scanf("%d", &testCases);
    while (testCases--) {
        scanf("%s", s);
        int length = strlen(s), segmentCount = 0;
        // 将字符串分段处理
        segmentType[segmentCount] = s[0];
        segmentLength[segmentCount] = 0;
        for (int i = 0; i < length; ++i) {
            if (s[i] != segmentType[segmentCount]) {
                ++segmentCount;
                segmentType[segmentCount] = s[i];
                segmentLength[segmentCount] = 0;
            }
            ++segmentLength[segmentCount];
        }
        ++segmentCount;
        int answer = 1;
        for (int i = 0; i < segmentCount; ++i) {
            // 处理固定字符段
            if (segmentType[i] != '?') {
                answer = max(answer, segmentLength[i]);
                continue;
            }
            // 处理问号段（不在边界的情况）
            if (i == 0 || i == segmentCount - 1) continue;
            if (segmentType[i - 1] == segmentType[i + 1]) {
                // 前后字符相同，偶数个问号会产生长度为2的段
                if ((segmentLength[i] & 1) == 0) answer = max(answer, 2);
            } else {
                // 前后字符不同，奇数个问号需要特殊处理
                if (segmentLength[i] & 1) {
                    if (segmentLength[i] != 1) answer = max(answer, 2);
                    else {
                        // 单个问号，选择延长较短的一侧
                        if (segmentLength[i - 1] > segmentLength[i + 1]) {
                            ++segmentLength[i + 1];
                        } else answer = max(answer, segmentLength[i - 1] + 1);
                    }
                }
            }
        }
        printf("Case %d: %d\n", ++caseNumber, answer);
    }
    return 0;
}
