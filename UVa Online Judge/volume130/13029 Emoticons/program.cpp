// Emoticons
// UVa ID: 13029
// Verdict: Accepted
// Submission Date: 2026-06-23
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        string s; cin >> s;
        int left = 0, waiting = 0, pending = 0, paired = 0;
        for (char c : s) {
            if (c == '^')
                if (waiting) waiting--, paired++;
                else if (pending > 0 && paired > 0) pending--, waiting++;
                else left++;
            else
                if (left) left--, waiting++;
                else if (paired > pending) pending++;
        }
        cout << "Case " << cs << ": " << paired << '\n';
    }
    return 0;
}
