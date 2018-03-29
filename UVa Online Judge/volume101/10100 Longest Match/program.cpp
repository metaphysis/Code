// Longest Match
// UVa ID: 10100
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

vector<string> s, t;

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
    while (getline(cin, line1))
    {
        getline(cin, line2);
        cout << setw(2) << right << ++cases << ". ";
        if (line1.length() == 0 || line2.length() == 0)
        {
            cout << "Blank!\n";
            continue;
        }
        
        s.clear();
        string block;
        for (auto c : line1)
        {
            if (isalpha(c) || isdigit(c)) block += c;
            else
            {
                if (block.length()) s.push_back(block);
                block.clear();
            }
        }
        if (block.length()) s.push_back(block);
        
        t.clear();
        block.clear();
        for (auto c : line2)
        {
            if (isalpha(c) || isdigit(c)) block += c;
            else
            {
                if (block.length()) t.push_back(block);
                block.clear();
            }
        }
        if (block.length()) t.push_back(block);

        cout << "Length of longest match: " << lcs() << '\n';
    }

    return 0;
}
