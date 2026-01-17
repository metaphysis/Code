// Send More Money
// UVa ID: 10782
// Verdict: Accepted
// Submission Date: 2026-01-07
// UVa Run Time: 0.480s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 用于存储每个字母对应的数字
int charToDigit[26];
// 用于标记数字是否已被使用
bool digitUsed[10];
// 存储所有出现的字母
vector<char> letters;
// 存储每个单词
vector<string> words;

// 回溯法尝试所有可能的数字映射
bool backtrack(int index) {
    // 如果所有字母都已分配数字，进行最终验证
    if (index == letters.size()) {
        // 检查是否所有单词的首字母不为0（除非单词只有一位）
        for (string &word : words)
            if (charToDigit[word[0] - 'A'] == 0 && word.size() > 1)
                return false;

        // 计算所有加数（前n-1个单词）的和
        long long sum = 0;
        for (int i = 0; i < words.size() - 1; ++i) {
            long long num = 0;
            for (char c : words[i])
                num = num * 10 + charToDigit[c - 'A'];
            sum += num;
        }

        // 计算结果单词（最后一个单词）对应的数字
        long long result = 0;
        string lastWord = words.back();
        for (char c : lastWord)
            result = result * 10 + charToDigit[c - 'A'];

        // 如果相等，则找到唯一解
        return sum == result;
    }

    char currentChar = letters[index];
    // 尝试为当前字母分配0-9中的一个未使用数字
    for (int digit = 0; digit <= 9; ++digit) {
        // 关键剪枝：如果当前字母是某个单词的首字母且单词长度>1，则不能为0
        bool isLeadingZero = false;
        if (digit == 0) {
            for (string &word : words) {
                if (word[0] == currentChar && word.size() > 1) {
                    isLeadingZero = true;
                    break;
                }
            }
        }
        if (isLeadingZero) continue;

        if (!digitUsed[digit]) {
            // 尝试赋值
            digitUsed[digit] = true;
            charToDigit[currentChar - 'A'] = digit;
            // 递归为下一个字母赋值
            if (backtrack(index + 1))
                return true; // 找到解，直接返回
            // 回溯，撤销当前选择
            digitUsed[digit] = false;
            charToDigit[currentChar - 'A'] = -1;
        }
    }
    // 当前字母尝试所有数字都失败，返回上一层
    return false;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        words.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> words[i];

        // 初始化全局数据结构
        fill(charToDigit, charToDigit + 26, -1);
        fill(digitUsed, digitUsed + 10, false);
        letters.clear();

        // 收集所有出现的不同字母
        set<char> letterSet;
        for (string &word : words)
            for (char c : word)
                letterSet.insert(c);
        // 将set转换为vector，方便按索引访问
        letters.assign(letterSet.begin(), letterSet.end());

        // 开始回溯搜索
        backtrack(0);

        // 准备输出：将（字母，数字）对存入向量并按字母排序
        vector<pair<char, int>> result;
        for (char c : letters)
            result.push_back({c, charToDigit[c - 'A']});
        sort(result.begin(), result.end());

        // 按格式输出结果
        for (size_t i = 0; i < result.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << result[i].first << '=' << result[i].second;
        }
        cout << '\n';
    }

    return 0;
}
