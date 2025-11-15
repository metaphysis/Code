// Frequent Substrings
// UVa ID: 10234
// Verdict: Accepted
// Submission Date: 2025-11-06
// UVa Run Time: 0.100s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

string toLowerString(const string& s) {
    string res = s;
    for (char& c : res) {
        c = tolower(c);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    while (getline(cin, S)) {
        // 转为小写
        S = toLowerString(S);
        int T;
        cin >> T;
        cin.ignore(); // 忽略换行

        for (int t = 0; t < T; ++t) {
            int N;
            cin >> N;
            cin.ignore();

            map<string, int> freq;
            int len = S.length();

            // 枚举所有长度为 N 的子串
            for (int i = 0; i <= len - N; ++i) {
                string sub = S.substr(i, N);
                freq[sub]++;
            }

            // 找出现次数最多且字典序最小的
            int maxCount = 0;
            string result;
            for (const auto& p : freq) {
                if (p.second > maxCount) {
                    maxCount = p.second;
                    result = p.first;
                } else if (p.second == maxCount && p.first < result) {
                    result = p.first;
                }
            }

            cout << maxCount << " " << result << "\n";
        }
    }

    return 0;
}
