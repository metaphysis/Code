// Chest of Drawers
// UVa ID: 11420
// Verdict: Accepted
// Submission Date: 2018-01-28
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

const int UNLOCKED = 0, LOCKED = 1;
long long dp[70][70][2];

long long dfs(int n, int s, int locked)
{
    if (n < 0 || s < 0) return 0;
    if (n == 1 && s == 1 && locked) dp[n][s][locked] = 1;
    if (n == 1 && s == 0 && !locked) dp[n][s][locked] = 1;
    if (dp[n][s][locked] < 0)
    {
        long long tmp;
        if (locked) tmp = dfs(n - 1, s - 1, UNLOCKED) + dfs(n - 1, s - 1, LOCKED);
        else tmp = dfs(n - 1, s, UNLOCKED) + dfs(n - 1, s + 1, LOCKED);
        dp[n][s][locked] = tmp;
    }
    return dp[n][s][locked];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, s;
    memset(dp, -1, sizeof(dp));
    while (cin >> n >> s, n > 0)
    {
        if (s > n)
        {
            cout << 0 << '\n';
            continue;
        }
        dfs(n, s, UNLOCKED);
        dfs(n, s, LOCKED);
        cout << (dp[n][s][LOCKED] + dp[n][s][UNLOCKED]) << '\n';
    }

    return 0;
}
