// Greatest K-Palindrome Substring
// UVa ID: 1239
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

struct operation
{
    int changed, deleted;
};

string line;
operation dp[1010][1010];
int k, maxLength;

int find(int i, int j)
{
    if (i >= j) return 0;
    if (dp[i][j].changed >= 0) return dp[i][j];

    if (line[i] == line[j])
    {
        find(i + 1, j - 1);
        dp[i][j].changed = dp[i + 1][j - 1].changed;
        dp[i][j].deleted = dp[i + 1][j - 1].deleted;
    }
    else
    {
        find(i + 1, j - 1);
        
        dp[i][j].changed = 1 + dp[i + 1][j - 1].changed;
        dp[i][j].deleted = 2 + dp[i + 1][j - 1].deleted;
        
        find(i, j - 1);
        dp[i][j].changed = min(dp[i][j].changed, dp[i + 1][j - 1].changed);
        dp[i][j].deleted = min(dp[i][j].deleted, 1 + dp[i + 1][j - 1].deleted);
        
        
        find(i + 1, j);
        dp[i][j].changed = min(dp[i][j].changed, dp[i + 1][j - 1].changed);
        dp[i][j].deleted = min(dp[i][j].deleted, 1 + dp[i + 1][j - 1].deleted);
    }

    if (dp[i][j].changed == k && dp[i][j].deleted == 0)
        maxLength = max(maxLength, j - i + 1);

    return dp[i][j];
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        cin >> line >> k;
        maxLength = 0;
        memset(dp, -1, sizeof(dp));
        find(0, line.length() - 1);
        cout << maxLength << '\n';
    }
    
    return 0;
}
