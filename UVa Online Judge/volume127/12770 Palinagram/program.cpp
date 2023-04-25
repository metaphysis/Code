// Palinagram
// UVa ID: 12770
// Verdict: Accepted
// Submission Date: 2023-04-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    int cnt[26];
    while (cin >> line) {
        if (line.front() == '#') break;
        memset(cnt, 0, sizeof cnt);
        for (auto c : line) cnt[c - 'a']++;
        string r;
        int t = 0;
        for (int i = 0; i < 26; i++)
            if (cnt[i] % 2 == 1)
                r += (char)('a' + i);
        if (r.length()) r.pop_back();
        cout << r << '\n';
    }
    return 0;
}
