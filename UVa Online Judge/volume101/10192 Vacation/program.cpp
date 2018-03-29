// Vacation
// UVa ID: 10192
// Verdict: Accepted
// Submission Date: 2018-03-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int IMINUS_JMINUS = 1, IMINUS = 2, JMINUS = 3;

struct state
{
    int length, from;
};

string s, t;

int lcs()
{
    state dp[s.size() + 1][t.size() + 1] = {};

    for (int i = 1; i <= s.size(); i++)
        for (int j = 1; j <= t.size(); j++)
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

    return dp[s.size()][t.size()].length;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    string line1, line2;
    while (getline(cin, s))
    {
        if (s == "#") break;
        getline(cin, t);
        cout << "Case #" << ++cases << ": you can visit at most " << lcs() << " cities." << '\n';
    }

    return 0;
}
