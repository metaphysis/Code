// String to Palindrome
// UVa ID: 10739
// Verdict: Accepted
// Submission Date: 2017-04-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dp[1010][1010];
string line;

int find(int i, int j)
{
    if (i >= j) return 0;
    if (dp[i][j] >= 0) return dp[i][j];

    if (line[i] == line[j])
        dp[i][j] = find(i + 1, j - 1);
    else
        dp[i][j] = 1 + min(find(i + 1, j - 1), min(find(i + 1, j), find(i, j - 1)));

    return dp[i][j];
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    cin.ignore(1024, '\n');

    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);

        memset(dp, -1, sizeof(dp));
        
        cout << "Case " << c << ": ";
        cout << find(0, line.length() - 1) << '\n';
    }
    
    return 0;
}
