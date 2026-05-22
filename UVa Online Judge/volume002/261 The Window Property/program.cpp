// The Windows Property
// UVa ID: 261
// Verdict: Accepted
// Submission Date: 2016-05-26
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0); cout.sync_with_stdio(false);
    // 预分配足够大的集合数组，用于存储不同长度的子串模式
    // 序列最长 100，因此窗口长度最大为 100，这里分配 1100 是冗余的
    vector<set<string>> pattern(1100);
    string line;
    while (getline(cin, line)) {
        // 清空所有集合，准备处理新序列
        for (int i = 0; i < pattern.size(); i++) pattern[i].clear();
        bool good = true;      // 标记当前序列是否仍具有窗口性质
        int position = -1;     // 记录第一个违规符号的位置（1-based）
        // 逐字符遍历输入序列
        for (int i = 0; i < line.length(); i++) {
            // 检查所有可能的窗口长度 k，从 1 到当前序列长度（i+1）
            for (int k = 1; k <= (i + 1); k++) {
                // 提取以当前字符结尾的长度为 k 的子串
                // 子串起始位置：i - k + 1，长度为 k
                string p = line.substr(i - k + 1, k);
                // 将子串插入到对应长度的集合中
                pattern[k].insert(p);
                // 如果不同子串的数量超过了 k+1，则窗口性质被破坏
                if (pattern[k].size() > (k + 1)) {
                    good = false;           // 标记为不具有窗口性质
                    position = i + 1;       // 记录违规符号位置（从 1 开始）
                    goto out;               // 跳出双重循环
                }
            }
        }
    out:        
        if (good) cout << "YES" << endl;
        else cout << "NO:" << position << endl;
    }
    return 0;
}
