// Longest Palindrome
// UVa ID: 11151
// Verdict: Accepted
// Submission Date: 2017-03-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    string s;

    cin >> cases;
    cin.ignore(1024, '\n');
    
    for (int c = 1; c <= cases; c++)
    {
        getline(cin, s);
        
        int memo[s.length() + 1][s.length() + 1];

        memset(memo, 0, sizeof(memo));

        for (int i = 1; i <= s.length(); i++)
            for (int j = 1; j <= s.length(); j++)
            {
                if (s[i - 1] == s[s.length() - j])
                    memo[i][j] = max(memo[i][j], memo[i - 1][j - 1] + 1);
                else
                    memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
            }
            
        cout << memo[s.length()][s.length()] << '\n';
    }
    
    return 0;
}
