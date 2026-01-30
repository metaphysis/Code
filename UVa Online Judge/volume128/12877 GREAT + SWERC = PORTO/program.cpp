// GREAT + SWERC = PORTO
// UVa ID: 12877
// Verdict: Accepted
// Submission Date: 2026-01-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

string words[16];  // 存储单词
int n, cnt;        // n: 单词数量, cnt: 解的数量
int value[26];     // 字母对应的数字，-1表示未分配
int used[10];      // 数字是否已被使用

// DFS搜索函数
// row: 当前处理的单词索引
// cln: 当前处理的列（从最低位0开始）
// sum: 当前列的累积和（包含进位）
void dfs(int row, int cln, int sum) {
    // 所有列处理完毕
    if (cln == words[n - 1].length()) {
        if (sum == 0) cnt++;  // 进位为0，找到一个解
        return;
    }
    // 当前列所有单词处理完毕，进入下一列
    if (row == n) {
        dfs(0, cln + 1, sum);
        return;
    }
    // 当前单词在当前列没有字母，跳过
    if (cln >= words[row].length()) {
        dfs(row + 1, cln, sum);
        return;
    }
    // 获取当前字母的索引（0-25对应A-Z）
    int c = words[row][cln] - 'A';
    // 处理加数（前n-1个单词）
    if (row < n - 1) {
        if (value[c] != -1) {
            // 字母已分配数字，检查是否是最高位且为0
            if (cln == words[row].size() - 1 && value[c] == 0) return;
            dfs(row + 1, cln, sum + value[c]);
        } else {
            // 字母未分配数字，尝试所有可能
            // 如果是最高位，不能为0（cln == words[row].size() - 1）
            for (int i = (cln == (words[row].size() - 1)); i < 10; i++)
                if (!used[i]) {
                    used[i] = 1;
                    value[c] = i;
                    dfs(row + 1, cln, sum + i);
                    value[c] = -1;  // 回溯
                    used[i] = 0;
                }
        }
    } else {
        // 处理结果（最后一个单词）
        int d = sum % 10;  // 当前列需要的数字
        // 结果单词的最高位不能为0
        if (cln == (words[n - 1].size() - 1) && d == 0) return;
        if (value[c] != -1) {
            // 结果字母已分配，检查是否匹配
            if (d == value[c])
                dfs(row + 1, cln, sum / 10);  // 处理进位
        } else {
            // 结果字母未分配，检查数字d是否可用
            if (!used[d]) {
                used[d] = 1;
                value[c] = d;
                dfs(row + 1, cln, sum / 10);  // 处理进位
                value[c] = -1;  // 回溯
                used[d] = 0;
            }
        }
    }
}

void solve() {
    // 读取单词并反转（从最低位开始处理）
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        reverse(words[i].begin(), words[i].end());
    }
    // 对加数单词排序（短单词优先，减少搜索深度）
    sort(words, words + n - 1, [](string a, string b) {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    });
    // 剪枝：结果长度不可能小于最大加数长度，也不可能大于最大加数长度+1
    if (words[n - 1].size() < words[n - 2].size() ||
        words[n - 2].size() + 2 <= words[n - 1].size()) {
        // 直接返回，输出0（在主函数中初始化cnt为0）
        return;
    }
    // 初始化
    cnt = 0;
    memset(value, -1, sizeof value);
    memset(used, 0, sizeof used);
    // 开始搜索
    dfs(0, 0, 0);
    // 输出结果
    cout << cnt << '\n';
}

int main() {
    // 加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 处理多个测试用例
    while (cin >> n) solve();
    return 0;
}
