// Emacs Plugin
// UVa ID: 12785
// Verdict: Accepted
// Submission Date: 2026-02-27
// UVa Run Time: 0.630s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 判断模式 p 是否匹配文本 t
bool match(const string &t, const string &p) {
    vector<string> segments;  // 存储按 '*' 分割后的段
    string cur;                // 当前正在累积的段
    
    // 将模式按 '*' 分割
    for (char c : p) {
        if (c == '*') {
            segments.push_back(cur);  // 将当前段加入列表
            cur.clear();               // 清空当前段
        } else {
            cur += c;                  // 累积字符
        }
    }
    segments.push_back(cur); // 将最后一段加入列表
    
    int pos = 0; // 当前在文本中的搜索起始位置
    // 依次匹配每个非空段
    for (const string &seg : segments) {
        if (seg.empty()) continue; // 空段（对应连续 * 或首尾 *）直接跳过
        size_t found = t.find(seg, pos); // 从 pos 开始查找 seg 第一次出现的位置
        if (found == string::npos) return false; // 找不到则匹配失败
        pos = found + seg.size(); // 更新搜索位置到该段末尾之后
    }
    return true; // 所有段都匹配成功
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) { // 处理多个测试用例
        string t;
        cin >> t; // 读入文本
        while (n--) {
            string p;
            cin >> p; // 读入模式
            cout << (match(t, p) ? "yes" : "no") << '\n';
        }
    }
    return 0;
}
