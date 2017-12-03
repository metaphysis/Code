// Coin Collector
// UVa ID: 11264
// Verdict: Accepted
// Submission Date: 2017-12-03
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, values[1010];
    
    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> n;

        int m = 2, s = 1;
        for (int i = 0; i < n; i++)
        {
            cin >> values[i];
            if (!i) continue;
            if (s < values[i - 1] && s + values[i - 1] < values[i])
                m++, s += values[i - 1];
        }
        cout << m << '\n';
    }

    return 0;
}
