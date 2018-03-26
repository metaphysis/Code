#include <bits/stdc++.h>

using namespace std;

const int IMINUS_JMINUS = 1, IMINUS = 2, JMINUS = 3;

struct state
{
    int length, from;
};

void lcs(string &s, string &t)
{
    state dp[s.length() + 1][t.length() + 1] = {};

    for (int i = 1; i <= s.length(); i++)
        for (int j = 1; j <= t.length(); j++)
            if (s[i - 1] == t[j - 1])
            {
                if (dp[i][j].length < dp[i - 1][j - 1].length + 1)
                {
                    dp[i][j].length = dp[i - 1][j - 1].length + 1;
                    dp[i][j].from = IMINUS_JMINUS;
                }
            }
            else
            {
                if (dp[i][j].length < dp[i - 1][j].length)
                    dp[i][j].length = dp[i - 1][j].length, dp[i][j].from = IMINUS;
                if (dp[i][j].length < dp[i][j - 1].length)
                    dp[i][j].length = dp[i][j - 1].length, dp[i][j].from = JMINUS;
            }

    cout << "LCS: length = " << dp[s.length()][t.length()].length;

    string subsequence;
    int endi = s.length(), endj = t.length();
    while (dp[endi][endj].from)
    {
        if (dp[endi][endj].from == IMINUS_JMINUS)
        {
            subsequence.push_back(s[endi - 1]);
            endi -= 1, endj -= 1;
        }
        else 
        {
            if (dp[endi][endj].from == IMINUS) endi -= 1;
            else endj -= 1;
        }
    }
    reverse(subsequence.begin(), subsequence.end());

    cout << " subsequence = " << subsequence << '\n';
}

int main(int argc, char *argv[])
{
    string s, t;
    while (cin >> s >> t) lcs(s, t);

    return 0;
}
