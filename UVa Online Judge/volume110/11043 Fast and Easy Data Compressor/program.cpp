// Fast and Easy Data Compressor
// UVa ID: 11043
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    // 读取全部输入字节（包括空格和换行）
    vector<unsigned char> inputBytes;
    int ch;
    while ((ch = cin.get()) != EOF)
        inputBytes.push_back((unsigned char)ch);
    int n = (int)inputBytes.size();

    // 预测表，初始化为 -1（表示尚无预测）
    int predictTable[256][256];
    memset(predictTable, -1, sizeof(predictTable));

    // 存储每个位置的结果：-1 表示 λ，否则为输出字节值
    vector<int> result(n, 0);
    for (int i = 0; i < n; ++i) {
        unsigned char cur = inputBytes[i];
        unsigned char prev2 = (i >= 2) ? inputBytes[i - 2] : 0;
        unsigned char prev1 = (i >= 1) ? inputBytes[i - 1] : 0;
        if (predictTable[prev2][prev1] == cur) {
            result[i] = -1; // 预测成功，不输出
        } else {
            result[i] = cur; // 输出该字符
            predictTable[prev2][prev1] = cur;
        }
    }

    // 分组输出
    int m = (n + 5) / 6; // ceil(n/6)
    for (int k = 0; k < m; ++k) {
        int desc = 64;
        vector<unsigned char> groupData;
        for (int j = 0; j < 6; ++j) {
            int idx = 6 * k + j;
            if (idx >= n) break; // 最后一组不足6个
            if (result[idx] == -1) {
                desc |= (1 << j); // 该位置为 λ
            } else {
                groupData.push_back((unsigned char)result[idx]);
            }
        }
        // 输出描述字节
        putchar((char)desc);
        // 输出该组所有非 λ 字节
        for (unsigned char b : groupData)
            putchar((char)b);
    }

    return 0;
}
