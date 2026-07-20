// Obfuscation
// UVa ID: 12131
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.280s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 特征键：首字母、尾字母、中间排序后的字符串
typedef tuple<char, char, string> Key;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int n;
        cin >> n;

        // 按长度分组，长度最大 100
        vector<map<Key, vector<string>>> dictByLen(101);
        for (int i = 0; i < n; ++i) {
            string w;
            cin >> w;
            int len = w.size();
            char first = w[0];
            char last = w[len - 1];
            string middle;
            if (len >= 2) middle = w.substr(1, len - 2);
            sort(middle.begin(), middle.end());
            Key key = make_tuple(first, last, middle);
            dictByLen[len][key].push_back(w);
        }

        int L = s.size();
        vector<int> dp(L + 1, 0);       // 0不可达，1唯一，2多种
        vector<int> prevPos(L + 1, -1);
        vector<string> prevWord(L + 1);

        dp[0] = 1;

        for (int i = 0; i < L; ++i) {
            if (dp[i] == 0) continue;
            int maxLen = min(100, L - i);
            for (int len = 1; len <= maxLen; ++len) {
                int j = i + len;
                string t = s.substr(i, len);
                char first = t[0];
                char last = t[len - 1];
                string mid;
                if (len >= 2) mid = t.substr(1, len - 2);
                sort(mid.begin(), mid.end());
                Key key = make_tuple(first, last, mid);

                auto it = dictByLen[len].find(key);
                if (it == dictByLen[len].end()) continue;

                // 所有匹配的单词都是有效选择
                for (const string& w : it->second) {
                    if (dp[i] == 1) {
                        if (dp[j] == 0) {
                            dp[j] = 1;
                            prevPos[j] = i;
                            prevWord[j] = w;
                        } else if (dp[j] == 1) {
                            dp[j] = 2;
                            // 不再唯一，前驱信息不再需要
                        }
                        // dp[j] == 2 则保持不变
                    } else { // dp[i] == 2
                        if (dp[j] == 0 || dp[j] == 1)
                            dp[j] = 2;
                        // 否则已是2
                    }
                }
            }
        }

        if (dp[L] == 0) {
            cout << "impossible\n";
        } else if (dp[L] == 2) {
            cout << "ambiguous\n";
        } else { // dp[L] == 1
            vector<string> words;
            int pos = L;
            while (pos > 0) {
                words.push_back(prevWord[pos]);
                pos = prevPos[pos];
            }
            reverse(words.begin(), words.end());
            for (size_t i = 0; i < words.size(); ++i) {
                if (i) cout << ' ';
                cout << words[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
