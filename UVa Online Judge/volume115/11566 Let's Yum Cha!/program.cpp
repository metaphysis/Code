// Let's Yum Cha!
// UVa ID: 11566
// Verdict: Accepted
// Submission Date: 2017-11-26
// UVa Run Time: 0.050s
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

int N, x, T, K;
int prices[110], favour[110], dp[24][1200];
    
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> x >> T >> K)
    {
        if (N == 0) break;

        for (int i = 1; i <= K; i++)
        {
            cin >> prices[i];
            
            int index;
            favour[i] = 0;
            for (int j = 0; j <= N; j++)
            {
                cin >> index;
                favour[i] += index;
            }
        }

        memset(dp, 0, sizeof(dp));
        int m = (N + 1) * x;
        for (int i = 1; i <= K; i++)
            for (int n = 2 * (min(N, i) + 1); n >= 1; n--)
                for (int j = m; j >= 1; j--)
                    for (int k = 0; k <= 2; k++)
                    {
                        if (n < k || j < k * prices[i]) continue;
                        dp[n][j] = max(dp[n][j], dp[n - k][j - k * prices[i]] + k * favour[i]);
                    }
        
        int maxFi = 0;
        for (int i = 1; i <= 2 * (N + 1) ; i++)
            for (int j = 1; j <= m; j++)
            {
                int c = (j + (N + 1) * T) * 11;
                if (c % 10 == 0) c /= 10;
                else c = c / 10 + 1;
                if (c <= m) maxFi = max(maxFi, dp[i][j]);
            }
        cout << fixed << setprecision(2) << (1.0 * maxFi / (N + 1)) << '\n';
    }

    return 0;
}
