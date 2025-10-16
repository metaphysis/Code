// Crazy Search
// UVa ID: 1123
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
using namespace std;
const int MAXHASH = 16000000;  // 最大哈希值范围
bool used[MAXHASH];            // 标记数组，记录哈希值是否出现过
int charMap[256];              // 字符到数字的映射表
char text[1000000];            // 输入文本缓冲区
int main() {
    int T;  // 测试用例数量
    scanf("%d", &T);
    while (T--) {
        int N, NC;  // N: 子串长度, NC: 字符集大小
        scanf("%d%d%s", &N, &NC, text);
        // 初始化字符映射表为-1
        memset(charMap, -1, sizeof(charMap));
        int id = 0;  // 当前分配的字符编号
        // 建立字符到数字的映射
        for (char *p = text; *p; p++)
            if (charMap[(int)*p] == -1)
                charMap[(int)*p] = id++;
        // 计算 NC^(N-1)，用于滑动窗口时移除最左字符
        int power = 1;
        for (int i = 1; i < N; i++) power *= NC;
        // 初始化标记数组
        memset(used, 0, sizeof(used));
        int hash = 0;           // 当前窗口的哈希值
        int len = strlen(text); // 文本长度
        int count = 0;          // 不同子串计数器
        // 滑动窗口处理所有子串
        for (int i = 0; i < len; i++) {
            // 加入新字符到哈希值
            hash = hash * NC + charMap[(int)text[i]];
            // 当窗口长度达到N时开始统计
            if (i >= N - 1) {
                // 如果该哈希值未出现过，计数并标记
                if (!used[hash]) {
                    used[hash] = true;
                    count++;
                }
                // 移除最左字符的贡献，为下一个窗口准备
                hash -= charMap[(int)text[i - N + 1]] * power;
            }
        }
        // 输出结果
        printf("%d\n", count);
        // 测试用例间输出空行
        if (T) printf("\n");
    }
    return 0;
}
