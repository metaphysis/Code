// The Most Potent Corner
// UVa ID: 10264
// Verdict: Accepted
// Submission Date: 2018-01-05
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int weight[1 << 15], sum[1 << 15], n;
    while (cin >> n)
    {
        int t = (1 << n);
        for (int i = 0; i < t; i++)
            cin >> weight[i];
        for (int i = 0; i < t; i++)
        {
            sum[i] = 0;
            for (int j = 0; j < n; j++)
            {
                int k = i ^ (1 << j);
                sum[i] += weight[k];
            }
        }
        int maxSum = 0;
        for (int i = 0; i < t; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int k = i ^ (1 << j);
                maxSum = max(maxSum, sum[i] + sum[k]);
            }
        }
        cout << maxSum << '\n';
    }

    return 0;
}
