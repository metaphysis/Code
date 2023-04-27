// Water Restrictions
// UVa ID: 11451
// Verdict: Accepted
// Submission Date: 2023-04-27
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
int L, S, C;
int s[16], c[16], r;
int m[16][16];
void dfs(int idx, int mask, int cnt) {
    if (cnt > C) return;
    if (idx == S || cnt == C ) {
        r = max(r, __builtin_popcount(mask));
        return;
    }
    for (int i = 0; i <= c[idx]; i++)
        dfs(idx + 1, mask | m[idx][i], cnt + i);
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> L >> S;
        for (int i = 0; i < S; i++) {
            cin >> s[i];
            s[i]--;
        }
        cin >> C;
        for (int i = 0; i < S; i++) cin >> c[i];
        for (int i = 0; i < S; i++)
            for (int j = 1; j <= c[i]; j++) {
                m[i][j] = 0;
                for (int k = s[i] - j; k <= s[i] + j; k++)
                    if (k >= 0 && k < L)
                        m[i][j] |= 1 << k;
            }   
        r = 0;
        dfs(0, 0, 0);
        cout << r << '\n';
    }
    return 0;
}
