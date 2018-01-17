// How Do You Add?
// UVa ID: 10943
// Verdict: Accepted
// Submission Date: 2018-01-17
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

int ways[128][128];

int search(int n, int k)
{
    if (ways[n][k] < 0)
    {
        if (n == 0 || k == 1) ways[n][k] = 1;
        else
        {
            ways[n][k] = 0;
            for (int i = 0; i <= n; i++)
            {
                ways[n][k] += search(n - i, k - 1);
                ways[n][k] %= 1000000;
            }
        }
    }
    return ways[n][k];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(ways, -1, sizeof(ways));
    search(110, 110);
        
    int N, K;           
    while (cin >> N >> K, N > 0)
        cout << ways[N][K] << '\n';

    return 0;
}
