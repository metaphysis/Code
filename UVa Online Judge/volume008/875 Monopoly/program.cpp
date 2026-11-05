// Monopoly
// UVa ID: 875
// Verdict: Accepted
// Submission Date: 2026-11-06
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 0; tc < T; ++tc) {
        int n;
        cin >> n;
        // tab[i][j] = 1 if letter j appears on the LHS of fact i,
        //           = 2 if letter j is the RHS of fact i (overwrites a 1).
        vector<vector<int>> tab(n, vector<int>(26, 0));
        for (int i = 0; i < n; ++i) {
            string fact;
            cin >> fact;
            int sep = (int)fact.find('>');
            for (int j = 0; j < sep; ++j) {
                tab[i][fact[j] - 'A'] = 1;
            }
            tab[i][fact[sep + 1] - 'A'] = 2;
        }
        // Column-pivot sweep, pivot row counter accidentally starts at 2.
        int cnt = 2;
        for (int j = 0; j < 26; ++j) {
            int pick = -1;
            // first look for a row with an LHS occurrence of letter j
            for (int i = cnt; i < n; ++i) {
                if (tab[i][j] == 1) { pick = i; break; }
            }
            // otherwise a row with an RHS occurrence of letter j
            if (pick == -1) {
                for (int i = cnt; i < n; ++i) {
                    if (tab[i][j] == 2) { pick = i; break; }
                }
            }
            if (pick != -1) {
                swap(tab[cnt], tab[pick]);
                ++cnt;
            }
        }
        if (tc > 0) cout << '\n';
        cout << cnt << '\n';
    }
    return 0;
}
