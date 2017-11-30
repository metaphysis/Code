// Exact Sum
// UVa ID: 11057
// Verdict: Accepted
// Submission Date: 2017-11-30
// UVa Run Time: 0.020s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int prices[10010], n, m;
    
    while (cin >> n)
    {
        for (int i = 0; i < n; i++) cin >> prices[i];
        sort(prices, prices + n);
        cin >> m;
        int k = lower_bound(prices, prices + n, m / 2) - prices;
        for (int i = k; i >= 0; i--)
            if (binary_search(prices + i + 1, prices + n, m - prices[i]))
            {
                cout << "Peter should buy books whose prices are ";
                cout << prices[i] << " and " << m - prices[i] << ".\n\n";
                break;
            }
    }
    
    return 0;
}
