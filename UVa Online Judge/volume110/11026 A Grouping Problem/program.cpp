// A Grouping Problem
// UVa ID: 11026
// Verdict: Accepted
// Submission Date: 2018-01-28
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// https://www.quora.com/How-can-I-solve-11026-A-Grouping-Problem-on-UVa-using-memoization

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

long long dp[1010][1010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, M, NUMBER[1010];
    while (cin >> N >> M, N > 0)
    {
        for (int i = 1; i <= N; i++)
            cin >> NUMBER[i];
        dp[0][0] = 1;
        for (int i = 1; i <= N; i++)
        {
            dp[i][0] = 1;
            for (int j = 1; j <= i; j++)
                dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * NUMBER[i]) % M;
        }
        long long biggest = 0;
        for (int i = 1; i <= N; i++)
            biggest = max(biggest, dp[N][i]);
        cout << biggest << '\n';
    }

    return 0;
}
