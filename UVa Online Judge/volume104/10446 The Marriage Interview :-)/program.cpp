// The Marriage Interview :-)
// UVa ID: 10446
// Verdict: Accepted
// Submission Date: 2018-01-20
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

unsigned long long dp[64][64];

unsigned long long trib(int n, int back)
{
    if (n <= 1) return 1;
    if (dp[n][back] > 0) return dp[n][back];
    dp[n][back] = 1;
    for (int i = 1; i <= back; i++)
        dp[n][back] += trib(n - i, back);
    return dp[n][back];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(dp, 0, sizeof(dp));

    int n, back, cases = 0;
    while (cin >> n >> back)
    {
        if (n > 60) break;
        cout << "Case " << ++cases << ": " << trib(n, back) << '\n';
    }

    return 0;
}
