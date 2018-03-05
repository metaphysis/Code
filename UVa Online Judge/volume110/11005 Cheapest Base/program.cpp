// Cheapest Base
// UVa ID: 11005
// Verdict: Accepted
// Submission Date: 2018-03-05
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

    int cases, costs[36], queries, n;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        cout << "Case " << c << ":\n";
        for (int i = 0; i < 36; i++)
            cin >> costs[i];
        cin >> queries;
        for (int i = 0; i < queries; i++)
        {
            cin >> n;
            int minCost = 0x3f3f3f3f;
            vector<int> result;
            for (int b = 2; b <= 36; b++)
            {
                int sum = 0, x = n;
                while (x)
                {
                    sum += costs[x % b];
                    x /= b;
                }
                if (sum < minCost)
                {
                    minCost = sum;
                    result.clear();
                    result.push_back(b);
                }
                else if (sum == minCost)
                {
                    result.push_back(b);
                }
            }
            cout << "Cheapest base(s) for number " << n << ":";
            for (auto r : result) cout << ' ' << r;
            cout << '\n';
        }
    }

    return 0;
}
