// Partitioning by Palindromes
// UVa ID: 11584
// Verdict: Accepted
// Submission Date: 2017-04-07
// UVa Run Time: 0.100s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string line;
int palindrome[1010][1010], dp[1010];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        
        line.insert(line.begin(), '#');
        memset(palindrome, 0, sizeof(palindrome));
        
        for (int i = 1; i < line.length(); i++)
        {
            for (int x = i, y = i; x >= 1 && y < line.length(); x--, y++)
            {
                if (line[x] != line[y]) break;
                palindrome[x][y] = 1;
            }

            if (i < line.length() - 1 && line[i] == line[i + 1])
            {
                for (int x = i, y = i + 1; x >= 1 && y < line.length(); x--, y++)
                {
                    if (line[x] != line[y]) break;
                    palindrome[x][y] = 1;
                }
            }
        }
            
        iota(dp, dp + 1010, 0);
        
        for (int i = 1; i <= line.length(); i++)
            for (int j = 0; j < i; j++)
                if (palindrome[j + 1][i])
                    dp[i] = min(dp[i], dp[j] + 1);

        cout << dp[line.length() - 1] << '\n';
    }
    
    return 0;
}
