// Longest Palindrome
// UVa ID: 11151
// Verdict: Accepted
// Submission Date: 2017-03-31
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;

    cin >> cases;
    cin.ignore(1024, '\n');
    
    for (int c = 1; c <= cases; c++)
    {
        string s, t;
        
        getline(cin, s);
        
        t.assign(s);
        reverse(t.begin(), t.end());
        
        int memo[s.length() + 1][t.length() + 1];

        memset(memo, 0, sizeof(memo));

        for (int i = 1; i <= s.length(); i++)
            for (int j = 1; j <= t.length(); j++)
                if (s[i - 1] == t[j - 1])
                    memo[i][j] = max(memo[i][j], memo[i - 1][j - 1] + 1);
                else
                    memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);

        cout << memo[s.length()][t.length()] << '\n';
    }
    
    return 0;
}
