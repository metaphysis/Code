// Winterim Backpacking Trip
// UVa ID: 907
// Verdict: Accepted
// Submission Date: 2017-04-09
// UVa Run Time: 0.000s
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

long long partition(long long data[], long long n, long long k)
{
    long long left = 0, right = 0;

    for (int i = 0; i < n; i++) right += data[i];
    
    while (left <= right)
    {
        long long middle = (left + right) / 2;
        long long j = 0, p = 0, sum = 0, ok = 1;

        while (j < n && p <= k)
        {
            if (sum + data[j] <= middle)
            {
                sum += data[j];
                j++;
            }
            else
            {
                sum = 0;
                p++;
            }
        }

        if (sum > 0) p++;

        if (p <= k)
            right = middle - 1;
        else
            left = middle + 1;
    }
    
    return left;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long N, K, dist[610];
    
    while (cin >> N >> K)
    {
        N++, K++;
        for (int i = 0; i < N; i++)
            cin >> dist[i];
        cout << partition(dist, N, K) << '\n';
    }
    
	return 0;
}
