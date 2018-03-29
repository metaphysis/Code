// AGTC
// UVa ID: 1207
// Verdict: Accepted
// Submission Date: 2018-03-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dp[1024][1024];

int med(string &S, string &T)
{
    dp[0][0] = 0;
    int M = S.length(), N = T.length();
    for (int i = 1; i <= M; i++) dp[i][0] = i;
    for (int j = 1; j <= N; j++) dp[0][j] = j;
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
        {
            int deleted = dp[i - 1][j] + 1;
            int inserted = dp[i][j - 1] + 1;
            int replaced = dp[i - 1][j - 1];
            if (S[i - 1] != T[j - 1]) replaced = dp[i - 1][j - 1] + 1;
            dp[i][j] = min(min(deleted, inserted), replaced);
        }
    return dp[M][N];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n1, n2;
    string s1, s2;
    while (cin >> n1)
    {
        cin >> s1 >> n2 >> s2;
        cout << med(s1, s2) << '\n';
    }

    return 0;
}
