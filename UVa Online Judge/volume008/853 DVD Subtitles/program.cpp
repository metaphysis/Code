// DVD Subtitles
// UVa ID: 853
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 处理一种语言的所有行，生成 行号集合 -> 词组 的映射
void processLines(int N, const vector<string>& lines, map<set<int>, string>& groups) {
    unordered_map<string, set<int>> wordLines;          // 单词 -> 行号集合
    for (int i = 0; i < N; ++i) {
        const string& line = lines[i];
        set<string> seen;                               // 当前行已出现的单词，用于去重
        string word;
        for (char ch : line) {
            if (isalpha(ch) || ch == '-') {             // 单词字符：字母或连字符
                word.push_back(tolower(ch));
            } else {
                if (!word.empty()) {
                    if (word.size() >= 3 && seen.find(word) == seen.end()) {
                        seen.insert(word);
                        wordLines[word].insert(i + 1);  // 行号从1开始
                    }
                    word.clear();
                }
            }
        }
        if (!word.empty()) {                            // 处理行尾单词
            if (word.size() >= 3 && seen.find(word) == seen.end()) {
                seen.insert(word);
                wordLines[word].insert(i + 1);
            }
        }
    }

    map<set<int>, vector<string>> groupMap;             // 行号集合 -> 该集合的所有单词
    for (const auto& kv : wordLines)
        if (kv.second.size() >= 2)                      // 只保留至少出现2行的单词
            groupMap[kv.second].push_back(kv.first);

    for (auto& kv : groupMap) {
        sort(kv.second.begin(), kv.second.end());
        string combined;
        for (size_t j = 0; j < kv.second.size(); ++j) {
            if (j > 0) combined += ' ';
            combined += kv.second[j];
        }
        groups[kv.first] = combined;                    // 生成最终词组
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    bool firstCase = true;
    while (T--) {
        int N;
        cin >> N;
        cin.ignore();                                   // 跳过行末换行

        vector<string> lines1(N), lines2(N);
        for (int i = 0; i < N; ++i) getline(cin, lines1[i]);
        for (int i = 0; i < N; ++i) getline(cin, lines2[i]);

        map<set<int>, string> groups1, groups2;
        processLines(N, lines1, groups1);
        processLines(N, lines2, groups2);

        vector<pair<string, string>> result;            // (L1词组, L2词组)
        for (const auto& kv : groups1) {
            auto it = groups2.find(kv.first);
            if (it != groups2.end())
                result.emplace_back(kv.second, it->second);
        }
        sort(result.begin(), result.end());             // 按L1词组排序

        if (!firstCase) cout << '\n';                   // 测试用例间空行
        firstCase = false;
        for (const auto& p : result)
            cout << p.first << '/' << p.second << '\n';
    }
    return 0;
}
