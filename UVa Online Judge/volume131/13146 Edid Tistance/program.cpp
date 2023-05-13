// Edid Tistance
// UVa ID: 13146
// Verdict: Accepted
// Submission Date: 2023-05-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dp[110][110];

int med(string &S, string &T) {
    dp[0][0] = 0;
    int M = S.length(), N = T.length();
    for (int i = 1; i <= M; i++) dp[i][0] = i;
    for (int j = 1; j <= N; j++) dp[0][j] = j;
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++) {
            int deleted = dp[i - 1][j] + 1;
            int inserted = dp[i][j - 1] + 1;
            int replaced = dp[i - 1][j - 1];
            if (S[i - 1] != T[j - 1]) replaced = dp[i - 1][j - 1] + 1;
            dp[i][j] = min(min(deleted, inserted), replaced);
        }
    return dp[M][N];
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    cin.ignore(256, '\n');
    while (T--) {
        string s1, s2;
        getline(cin, s1);
        getline(cin, s2);
        s1.insert(s1.begin(), '#');
        s2.insert(s2.begin(), '#');
        cout << med(s1, s2) << '\n';
    }
    return 0;
}
