// Test the Rods
// UVa ID: 10086
// Verdict: Accepted
// Submission Date: 2018-01-27
// UVa Run Time: 0.050s
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

const int INF = 0x3fffffff;
int T1, T2, n, dp[32][310][310], memo[32][310][310];
int rods[32] = {0}, ncpc[32][24], bcew[32][24];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> T1 >> T2)
    {
        if (T1 == 0 && T2 == 0) break;

        memset(ncpc, 0, sizeof(ncpc));
        memset(bcew, 0, sizeof(bcew));

        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> rods[i];
            for (int j = 1; j <= rods[i]; j++)
                cin >> ncpc[i][j];
            for (int j = 1; j <= rods[i]; j++)
                cin >> bcew[i][j];
        }

        for (int i = 1; i <= n; i++)
            rods[i] += rods[i - 1];

        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= T1; j++)
                for (int k = 0; k <= T2; k++)
                    dp[i][j][k] = INF;

        dp[0][0][0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= rods[i - 1]; j++)
            {
                int t1 = j, t2 = rods[i - 1] - t1;
                if (t1 <= T1 && t2 <= T2)
                {
                    int rod = rods[i] - rods[i - 1];
                    for (int k = 0; k <= rod; k++)
                    {
                        if (t1 + k <= T1 && t2 + rod - k <= T2)
                        {
                            if (dp[i - 1][t1][t2] + ncpc[i][k] + bcew[i][rod - k] < dp[i][t1 + k][t2 + rod - k])
                            {
                                dp[i][t1 + k][t2 + rod - k] = dp[i - 1][t1][t2] + ncpc[i][k] + bcew[i][rod - k];
                                memo[i][t1 + k][t2 + rod - k] = k;
                            }
                        }
                    }
                }
            }
        }

        int cost = INF;
        int last = n, t1 = 0, t2 = 0;
        for (int j = 0; j <= T1; j++)
            for (int k = 0; k <= T2; k++)
                if (dp[last][j][k] < cost)
                    cost = dp[last][j][k], t1 = j, t2 = k;
        cout << cost << '\n';

        vector<int> samples;
        while (last > 0)
        {
            int tested = memo[last][t1][t2];
            samples.push_back(tested);
            t1 -= tested;
            t2 -= (rods[last] - rods[last - 1] - tested);
            last -= 1;
        }
        reverse(samples.begin(), samples.end());
        for (int i = 0; i < samples.size(); i++)
        {
            if (i) cout << ' ';
            cout << samples[i];
        }
        cout << "\n\n";
    }

    return 0;
}
