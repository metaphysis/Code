// Lexicographically Smallest FPIS
// UVa ID: 13088
// Verdict: Accepted
// Submission Date: 2025-12-13
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int n = s.length();
        set<char> chars(s.begin(), s.end());
        vector<char> sortedChars(chars.begin(), chars.end());
        int k = sortedChars.size();

        string result;
        int used = 0;
        for (int i = 0; i < k; i++) {
            int needAfter = k - i - 1;          // 后面还需要保证的字符种类数
            int canTake = n - used - needAfter; // 当前字符能放的最大数量
            // 将当前字符重复 canTake 次加入结果
            for (int j = 0; j < canTake; j++) {
                result += sortedChars[i];
                used++;
            }
        }
        cout << result << endl;
    }
    return 0;
}
