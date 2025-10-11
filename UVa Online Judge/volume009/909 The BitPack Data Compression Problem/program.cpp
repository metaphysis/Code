// The BitPack Data Compression Problem
// UVa ID: 909
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dp[65536];      // dp[i] = 压缩前 i 个字符的最小字节数
int cmdCode[65536]; // 到达 i 时最后一条指令的 n 值
int from[65536];    // 前一个状态的位置
int n;              // 输入字符串长度
int outputByteCount;// 输出字节数（用于调试）
char str[65536];    // 输入字符串，下标从 1 开始

// 回溯输出压缩结果
void outputCompressed(int pos) {
    if (pos == 0) return;
    if (cmdCode[pos] >= 129) {
        // 重复指令：cmdCode[pos] 和 1 个字符
        outputCompressed(from[pos]);
        printf("%c%c", cmdCode[pos], str[pos]);
        outputByteCount += 2;
    } else {
        // 文字指令：cmdCode[pos] 和 (cmdCode[pos] + 1) 个字符
        outputCompressed(from[pos]);
        printf("%c", cmdCode[pos]);
        outputByteCount++;
        int literalLen = cmdCode[pos];
        for (int j = literalLen; j >= 0; j--) {
            printf("%c", str[pos - j]);
            outputByteCount++;
        }
    }
}

int main(int argc, char* argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int idx = 1;
    char ch;
    // 读入输入到 str[1..n]
    while ((ch = getchar()) != EOF) str[idx++] = ch;
    n = strlen(str + 1);
    assert(n < 65536);
    // 初始化 dp 为一个大数
    memset(dp, 63, sizeof(dp));
    dp[0] = 0;
    // 动态规划
    for (int i = 0; i <= n; i++) {
        // 尝试重复指令
        int repeatCount = 0;
        for (int j = i + 1; j <= n; j++) {
            if (str[j] == str[i + 1]) {
                repeatCount++;
                if (repeatCount + 127 > 255) break;
                if (repeatCount >= 2) {
                    if (dp[j] > dp[i] + 2) {
                        cmdCode[j] = repeatCount + 127;
                        from[j] = i;
                    }
                    dp[j] = min(dp[j], dp[i] + 2);
                }
            } else break;
        }
        // 尝试文字指令
        int literalCount = 0;
        for (int j = i + 1; j <= n; j++) {
            literalCount++;
            if (literalCount - 1 > 127) break;
            if (dp[j] > dp[i] + literalCount + 1) {
                cmdCode[j] = literalCount - 1;
                from[j] = i;
            }
            dp[j] = min(dp[j], dp[i] + literalCount + 1);
        }
    }
    outputByteCount = 0;
    outputCompressed(n);
    return 0;
}
