// Approximate Matches
// UVa ID: 363
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

int lcs(string& s, string& t)
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

    return memo[s.length()][t.length()][0];
}

void generate(string S, string P, int k)
{
    set<string> produced;
    for (int i = 0; i < S.length(); i++)
        for (int j = 1; j <= S.length() - i; j++)
        {
            string S1 = S.substr(i, j);
            if (produced.find(S1) != produced.end()) continue;
            produced.insert(S1);
            int matches = lcs(S1, P);
            int mismatches = S1.length() + P.length() - 2 * matches;
            if (mismatches <= k)
            {
                if (mismatches == 0) cout << S1 << " matches " << P << '\n';
                else if (mismatches == 1) cout << S1 << " matches " << P << " with 1 mismatch\n";
                else cout << S1 << " matches " << P << " with " << mismatches << " mismatches\n";
            }
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int k;
    string S, P;
    while (cin >> k, k >= 0)
    {
        cin.ignore(1024, '\n');
        getline(cin, S);
        getline(cin, P);
        generate(S, P, k);
        cout << '\n';
    }
    
	return 0;
}
