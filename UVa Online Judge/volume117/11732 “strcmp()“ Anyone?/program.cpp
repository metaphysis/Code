// "strcmp()" Anyone?
// UVa ID: 11732
// Verdict: Accepted
// Submission Date: 2025-10-17
// UVa Run Time: 0.690s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// 计算两个字符串的最长公共前缀长度
int computeLCP(const string &a, const string &b) {
    int len = 0;
    int min_len = min(a.length(), b.length());  // 取两字符串长度的最小值
    while (len < min_len && a[len] == b[len])   // 逐个字符比较直到不同或结束
        len++;
    return len;
}

int main() {
    ios::sync_with_stdio(false);  // 关闭同步，提高I/O速度
    cin.tie(0);                   // 解除cin与cout的绑定
    int N, caseNo = 1;  // N: 字符串数量, caseNo: 测试用例编号
    while (cin >> N && N) {  // 读取N直到遇到0
        vector<string> strings(N);
        for (int i = 0; i < N; i++)
            cin >> strings[i];  // 读取所有字符串
        // 对字符串进行字典序排序，使具有公共前缀的字符串相邻
        sort(strings.begin(), strings.end());
        // lcp[i] 存储 strings[i-1] 和 strings[i] 的最长公共前缀长度
        // lcp[0] 未使用，从 lcp[1] 开始有效
        vector<int> lcp(N, 0);
        for (int i = 1; i < N; i++) lcp[i] = computeLCP(strings[i-1], strings[i]);
        long long totalComparisons = 0;  // 总比较次数
        // 遍历所有字符串对 (i, j)，其中 i < j
        for (int i = 0; i < N; i++) {
            int min_lcp = INT_MAX;  // 初始化最小LCP为最大值
            for (int j = i + 1; j < N; j++) {
                // 更新从 i+1 到 j 的最小LCP
                // 根据LCP区间最小值性质：LCP(i,j) = min(lcp[i+1], ..., lcp[j])
                if (j == i + 1) {
                    min_lcp = lcp[j];  // 第一个相邻对，直接取lcp[j]
                } else {
                    min_lcp = min(min_lcp, lcp[j]);  // 更新区间最小值
                }
                // 确定实际的LCP长度
                // 如果字符串完全相同，实际LCP应该是字符串长度，而不是min_lcp
                int actual_lcp = min_lcp;
                if (strings[i] == strings[j]) {
                    actual_lcp = strings[i].length();  // 相同字符串的LCP等于自身长度
                }
                // 根据字符串是否相同计算比较次数
                if (strings[i] == strings[j]) {
                    // 完全相同的情况：比较次数 = 2 * 字符串长度 + 2
                    totalComparisons += 2 * actual_lcp + 2;
                } else {
                    // 不同字符串：比较次数 = 2 * LCP长度 + 1
                    totalComparisons += 2 * actual_lcp + 1;
                }
            }
        }
        // 输出结果
        cout << "Case " << caseNo++ << ": " << totalComparisons << "\n";
    }
    return 0;
}
