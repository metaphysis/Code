// Text Formalization
// UVa ID: 10584
// Verdict: Accepted
// Submission Date: 2026-06-28
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 解析一行 ""xxx" -> "yyy""，返回 {原词, 展开}
pair<string, string> parseLine(const string& line) {
    size_t p1 = line.find('"');
    size_t p2 = line.find('"', p1 + 1);
    string first = line.substr(p1 + 1, p2 - p1 - 1);
    size_t arrow = line.find("->", p2 + 1);
    size_t p3 = line.find('"', arrow + 2);
    size_t p4 = line.find('"', p3 + 1);
    string second = line.substr(p3 + 1, p4 - p3 - 1);
    return {first, second};
}

// 全大写
string toUpperAll(const string& s) {
    string res = s;
    for (char& c : res) if (isalpha(c)) c = toupper(c);
    return res;
}

// 首字母大写（其余字符不变）
string capitalizeFirst(const string& s) {
    string res = s;
    if (!res.empty() && isalpha(res[0]))
        res[0] = toupper(res[0]);
    return res;
}

// 处理一行，返回展开后的字符串
string expandLine(const string& s,
                  const vector<pair<string, string>>& patterns,   // 缩略词及展开（已按优先级排好）
                  const vector<pair<string, string>>& acronyms,   // 首字母缩略词
                  vector<bool>& used) {
    string ans;
    int pos = 0, n = (int)s.size();

    while (pos < n) {
        bool matched = false;

        // 1. 匹配缩略词（优先级已体现在 patterns 顺序中）
        for (const auto& p : patterns) {
            const string& pat = p.first;
            if (s.compare(pos, pat.size(), pat) == 0) {
                ans += p.second;
                pos += pat.size();
                matched = true;
                break;
            }
        }
        if (matched) continue;

        // 2. 匹配首字母缩略词（仅当未使用过）
        for (size_t i = 0; i < acronyms.size(); ++i) {
            if (used[i]) continue;
            const string& pat = acronyms[i].first;
            if (s.compare(pos, pat.size(), pat) == 0) {
                ans += acronyms[i].second + " (" + pat + ")";
                used[i] = true;
                pos += pat.size();
                matched = true;
                break;
            }
        }
        if (matched) continue;

        // 无匹配，复制普通字符
        ans += s[pos++];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C, A;
    cin >> C >> A;
    cin.ignore();   // 跳过行尾换行

    vector<pair<string, string>> patterns;   // 所有缩略词形式（优先级：原样 → 全大写 → 首字母大写）
    for (int i = 0; i < C; ++i) {
        string line;
        getline(cin, line);
        auto p = parseLine(line);
        patterns.push_back(p);   // 原样
        patterns.push_back({toUpperAll(p.first), toUpperAll(p.second)});   // 全大写
        if (islower(p.first[0]))   // 若首字母可大写，添加首字母大写形式
            patterns.push_back({capitalizeFirst(p.first), capitalizeFirst(p.second)});
    }

    vector<pair<string, string>> acronyms;
    for (int i = 0; i < A; ++i) {
        string line;
        getline(cin, line);
        acronyms.push_back(parseLine(line));
    }

    // 逐段处理文本
    while (true) {
        vector<bool> used(A, false);   // 每段文本重置首字母缩略词使用状态
        bool hasText = false;

        while (true) {
            string line;
            if (!getline(cin, line)) break;
            if (line == "#") break;
            hasText = true;
            cout << expandLine(line, patterns, acronyms, used) << '\n';
        }

        if (!hasText) break;   // 文件结束或空文本
        cout << "#\n";         // 保留原文本分隔符
    }

    return 0;
}
