// Hnepig Arnde
// UVa ID: 12724
// Verdict: Accepted
// Submission Date: 2026-02-27
// UVa Run Time: 0.160s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算单词去掉首尾后中间部分排序后的字符串
string middleSorted(const string &s) {
    if (s.length() <= 2) return "";
    string mid = s.substr(1, s.length() - 2);
    sort(mid.begin(), mid.end());
    return mid;
}

int main() {
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int N, M;
        cin >> N >> M;
        vector<string> dict(N);
        for (int i = 0; i < N; ++i) cin >> dict[i];

        // 预处理字典中每个单词的中间部分排序后的结果
        vector<string> midSortedDict(N);
        for (int i = 0; i < N; ++i)
            midSortedDict[i] = middleSorted(dict[i]);

        cout << "Case #" << caseNum << ":\n";

        // 读掉第一行末尾的换行符
        cin.ignore();

        for (int line = 0; line < M; ++line) {
            string lineStr;
            getline(cin, lineStr);
            istringstream iss(lineStr);
            string word;
            bool firstWord = true;
            while (iss >> word) {
                if (!firstWord) cout << ' ';
                firstWord = false;

                // 在字典中找匹配的单词
                for (int i = 0; i < N; ++i) {
                    if (dict[i].length() != word.length()) continue;
                    if (dict[i][0] != word[0]) continue;
                    if (dict[i].back() != word.back()) continue;
                    if (middleSorted(word) != midSortedDict[i]) continue;
                    // 匹配成功
                    cout << dict[i];
                    break;
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
