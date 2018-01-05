// Jollybee Tournament
// UVa ID: 1241
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

    int cases, n, m, p, bits[1024];
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        fill(bits, bits + 1024, 1);
        for (int i = 1; i <= m; i++)
        {
            cin >> p;
            bits[p - 1] = 0;
        }
        int wo = 0;
        for (int i = n; i >= 1; i--)
        {
            int t = (1 << i);
            for (int j = 0, k = 0; j < t; j += 2, k++)
            {
                if (bits[j] ^ bits[j + 1]) wo++;
                bits[k] = bits[j] | bits[j + 1];
            }
        }
        cout << wo << '\n';
    }

    return 0;
}
