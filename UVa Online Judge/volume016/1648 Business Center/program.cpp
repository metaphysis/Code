// Business Center
// UVa ID: 1648
// Verdict: Accepted
// Submission Date: 2018-01-28
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

    int n, m, u, d;
    while (cin >> n >> m)
    {
        int lowest = 0x7fffffff;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> d;
            int x = (n * u) / (u + d);
            if ((n * u) % (u + d) == 0) x--;
            lowest = min(lowest, n * u - (u + d) * x);
        }
        cout << lowest << '\n';
    }

    return 0;
}
