// SMS
// UVa ID: 11171
// Verdict: Accepted
// Submission Date: 2026-05-30
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// 字母到数字的映射
int charToDigit(char c) {
    if (c <= 'c') return 2;
    if (c <= 'f') return 3;
    if (c <= 'i') return 4;
    if (c <= 'l') return 5;
    if (c <= 'o') return 6;
    if (c <= 's') return 7;
    if (c <= 'v') return 8;
    return 9;
}

// 将单词转换为数字串
string encode(const string& word) {
    string res;
    for (char c : word) res += char('0' + charToDigit(c));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    while (cin >> N, N) {
        // 按数字串分组存储单词
        unordered_map<string, vector<string>> dict;
        vector<string> words(N);
        for (int i = 0; i < N; ++i) {
            cin >> words[i];
            dict[encode(words[i])].push_back(words[i]);
        }

        // 构建单词 -> (数字串, (排名, 总单词数)) 的映射
        unordered_map<string, pair<string, pair<int, int>>> rankMap;
        for (auto& p : dict) {
            string code = p.first;
            auto& lst = p.second;
            int total = lst.size();
            for (int i = 0; i < total; ++i) {
                rankMap[lst[i]] = {code, {i, total}};
            }
        }

        int Q;
        cin >> Q;
        while (Q--) {
            string target;
            cin >> target;
            int L = target.size();

            // dp[i]: 前缀 [0, i) 的最小代价
            vector<int> dp(L + 1, INF);
            // pre[i]: 上一段的起始位置
            vector<int> pre(L + 1, -1);
            // partLen[i]: 当前段的长度
            vector<int> partLen(L + 1, 0);
            dp[0] = 0;

            // 动态规划
            for (int i = 0; i < L; ++i) {
                if (dp[i] == INF) continue;
                string cur;
                // 枚举单词长度，最长 10
                for (int j = i; j < min(L, i + 10); ++j) {
                    cur += target[j];
                    auto it = rankMap.find(cur);
                    if (it != rankMap.end()) {
                        int rank = it->second.second.first;
                        int total = it->second.second.second;
                        // 切换代价
                        int switchCost = (rank > 0) ? min(rank, total - rank) : 0;
                        int wordCost = (int)cur.size() + switchCost;
                        // R 键代价（最后一段不加）
                        int rCost = (j + 1 == L) ? 0 : 1;
                        int totalCost = dp[i] + wordCost + rCost;
                        if (totalCost < dp[j + 1]) {
                            dp[j + 1] = totalCost;
                            pre[j + 1] = i;
                            partLen[j + 1] = j - i + 1;
                        }
                    }
                }
            }

            // 回溯得到拆分方案
            vector<string> parts;
            int pos = L;
            while (pos > 0) {
                int start = pre[pos];
                string w = target.substr(start, partLen[pos]);
                parts.push_back(w);
                pos = start;
            }
            reverse(parts.begin(), parts.end());

            // 输出结果
            for (size_t idx = 0; idx < parts.size(); ++idx) {
                string& w = parts[idx];
                string code = rankMap[w].first;
                int rank = rankMap[w].second.first;
                int total = rankMap[w].second.second;

                // 输出数字串
                cout << code;

                // 输出 U/D 操作
                if (rank > 0) {
                    int upCnt = rank;
                    int downCnt = total - rank;
                    if (upCnt <= downCnt) {
                        if (upCnt == 1) cout << "U";
                        else cout << "U(" << upCnt << ")";
                    } else {
                        if (downCnt == 1) cout << "D";
                        else cout << "D(" << downCnt << ")";
                    }
                }

                // 输出 R（最后一段不加）
                if (idx + 1 < parts.size()) cout << "R";
            }
            cout << "\n";
        }
    }
    return 0;
}
