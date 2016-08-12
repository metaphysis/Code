#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

void lcs(string& s, string& t)
{
    int memo[s.length() + 1][t.length() + 1][2];

    memset(memo, 0, sizeof(memo));

    for (int i = 1; i <= s.length(); i++)
        for (int j = 1; j <= t.length(); j++)
            if (s[i - 1] == t[j - 1])
            {
                if (memo[i][j][0] < memo[i - 1][j - 1][0] + 1)
                {
                    memo[i][j][0] = memo[i - 1][j - 1][0] + 1;
                    memo[i][j][1] = 1;
                }
            }
            else
            {
                if (memo[i][j][0] < memo[i - 1][j][0])
                {
                    memo[i][j][0] = memo[i - 1][j][0];
                    memo[i][j][1] = 2;
                }

                if (memo[i][j][0] < memo[i][j - 1][0])
                {
                    memo[i][j][0] = memo[i][j - 1][0];
                    memo[i][j][1] = 3;
                }
            }

    cout << "LCS: length = " << memo[s.length()][t.length()][0];

    string subsequence;
    int endi = s.length(), endj = t.length();
    while (memo[endi][endj][1] > 0)
    {
        if (memo[endi][endj][1] == 1)
        {
            subsequence.push_back(s[endi - 1]);
            endi -= 1, endj -= 1;
        }
        else if (memo[endi][endj][1] == 2)
            endi -= 1;
        else
            endj -= 1;
    }
    reverse(subsequence.begin(), subsequence.end());

    cout << " subsequence = " << subsequence << '\n';
}

int main(int argc, char *argv[])
{
    string s, t;
    while (cin >> s >> t)
        lcs(s, t);

    return 0;
}
