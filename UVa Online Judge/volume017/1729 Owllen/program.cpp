// Owllen
// UVa ID: 1729
// Verdict: Accepted
// Submission Date: 2025-11-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; ++cs) {
        string s;
        cin >> s;
        vector<int> f(26, 0);
        for (char ch : s) f[ch - 'a']++;
        // 如果所有字母都出现过，频次至少为 1
        // 如果某个字母没出现，频次为 0
        // 但注意：如果所有字母都出现，频次是出现次数最少的字母的次数
        // 但题目要求最小 LCS 长度，实际上就是频次
        // 因为我们可以让 T 全部由出现次数最少的那个字母组成
        int cnt = *min_element(f.begin(), f.end());
        assert(cnt > 0);
        cout << "Case " << cs << ": " << cnt << '\n';
    }
    return 0;
}
