int dp[1024][1024];

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
