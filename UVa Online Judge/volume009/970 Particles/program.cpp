// Particles
// UVa ID: 970
// Verdict: Accepted
// Submission Date: 2018-11-26
// UVa Run Time: 0.350s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dp[110][110][3], visited[110][110];

void setResult(int i, int j, int m, int n)
{
    if (dp[i][j][0])
    {
        if (dp[m][n][0]) dp[i][n][1] = 1;
        if (dp[m][n][1]) dp[i][n][0] = 1;
        if (dp[m][n][2]) dp[i][n][2] = 1;
    }
    if (dp[i][j][1])
    {
        if (dp[m][n][0]) dp[i][n][0] = 1;
        if (dp[m][n][1]) dp[i][n][1] = 1;
        if (dp[m][n][2]) dp[i][n][1] = 1;
    }
    if (dp[i][j][2])
    {
        if (dp[m][n][0]) dp[i][n][2] = 1;
        if (dp[m][n][1]) dp[i][n][1] = 1;
        if (dp[m][n][2]) dp[i][n][0] = 1;
    }
}

void dfs(int i, int j)
{
    if (visited[i][j] || i == j) return;
    visited[i][j] = 1;
    for (int k = i; k < j; k++)
    {
        dfs(i, k);
        dfs(k + 1, j);
        setResult(i, k, k + 1, j);
        if (dp[i][j][0] && dp[i][j][1] && dp[i][j][2]) break;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    string sequences;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> sequences;
        memset(visited, 0, sizeof(visited));
        memset(dp, 0, sizeof(dp));
        int L = sequences.length();
        for (int i = 0; i < L; i++)
            dp[i][i][sequences[i] - 'X'] = 1; 
        dfs(0, L - 1);
        if (dp[0][L - 1][2]) cout << "Z\n";
        else if (dp[0][L - 1][1]) cout << "Y\n";
        else cout << "X\n";
    }
    
    return 0;
}
