// The Marriage Interview :-)
// UVa ID: 10446
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

int dp[64][64] = {0};

int trib(int n, int back)
{
    if (dp[n][back]) return dp[n][back];
    int count = 1;
    if (n <= 1) return dp[n][back] = count;
    else
    {
        for (int i = 1; i <= back; i++)
            count += trib(n - i, back);
    }
    return dp[n][back] = count;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(dp, 0, sizeof(dp));
    trib(62, 62);

    int n, back, cases = 0;
    while (cin >> n >> back)
        cout << "Case " << ++cases << ": " << dp[n][back] << '\n';

    return 0;
}
