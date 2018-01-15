// Exact Change
// UVa ID: 11517
// Verdict: Accepted
// Submission Date: 2018-01-15
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

    int cases, coins[110], n, price, paid[20010];
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> price >> n;
        for (int i = 0; i < n; i++)
            cin >> coins[i];
            
        memset(paid, -1, sizeof(paid));
        paid[0] = 0;
        
        for (int i = 0; i < n; i++)
            for (int j = price; j >= 0; j--)
                if (paid[j] >= 0)
                {
                    if (paid[j + coins[i]] < 0 || (paid[j] + 1 < paid[j + coins[i]]))
                        paid[j + coins[i]] = paid[j] + 1;
                }
        for (int j = price; j <= 20000; j++)
            if (paid[j] > 0)
            {
                cout << j << ' ' << paid[j] << '\n';
                break;
            }
    }

    return 0;
}
