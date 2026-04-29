#include <bits/stdc++.h>

using namespace std;

pair<int, int> lcs(string &s, string &t)
{
    if (s.length() == 0 || t.length() == 0) return make_pair(-1, -1);

    int start = 0, length = 0;
    int dp[s.length() + 1][t.length() + 1] = {};

    for (int i = 1; i <= s.length(); i++)
        for (int j = 1; j <= t.length(); j++)
        {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = 0;
                
            if (dp[i][j] > length)
            {
                length = dp[i][j];
                start = i - dp[i][j];
            }
        }

    return make_pair(start, length);
}

int main(int argc, char *argv[])
{
    string s, t;
    while (cin >> s >> t) lcs(s, t);

    return 0;
}
