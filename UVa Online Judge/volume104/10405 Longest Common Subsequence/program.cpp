// Longest Common Subsequence
// UVa ID: 10405
// Verdict: Accepted
// Submission Date: 2018-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int memo[1010][1010];

void lcs(string &s, string &t)
{
    for (int i = 0; i <= s.length(); i++)
        for (int j = 0; j <= t.length(); j++)
            memo[i][j] = 0;

    for (int i = 1; i <= s.length(); i++)
        for (int j = 1; j <= t.length(); j++)
            if (s[i - 1] == t[j - 1])
            {
                if (memo[i][j] < memo[i - 1][j - 1] + 1)
                    memo[i][j] = memo[i - 1][j - 1] + 1;
            }
            else
            {
                if (memo[i][j] < memo[i - 1][j])
                    memo[i][j] = memo[i - 1][j];

                if (memo[i][j] < memo[i][j - 1])
                    memo[i][j] = memo[i][j - 1];
            }

    cout << memo[s.length()][t.length()] << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string s, t;
    while (getline(cin, s))
    {
        getline(cin, t);
        lcs(s, t);
    }

    return 0;
}
