// Period
// UVa ID: 1328
// Verdict: Accepted
// Submission Date: 2024-11-23
// UVa Run Time: 0.110s

// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int N, cases = 1;
    string s;
    while (cin >> N) {
        if (N == 0) break;
        cin >> s;
        cout << "Test case #" << cases++ << '\n';
        int fail[1000010];
        fail[0] = -1;
        int i = 0, j = -1;
        while (i < s.length())
            if (j == -1 || s[i] == s[j]) i++, j++, fail[i] = j;
            else j = fail[j];
        for (int i = 1; i <= s.length(); i++)
            if (fail[i] && i % (i - fail[i]) == 0)
                cout << i << ' ' << i / (i - fail[i]) << '\n';
        cout << '\n';
    }
    return 0;
}
