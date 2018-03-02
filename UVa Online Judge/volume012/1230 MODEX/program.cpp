// MODEX
// UVa ID: 1230
// Verdict: Accepted
// Submission Date: 2018-03-02
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

long long powerMod(long long x, long long y, long long n)
{
    if (y == 1) return x % n;
    if (y % 2 == 1)
    {
        long long r = powerMod(x, y / 2, n);
        return ((r % n) * (r % n) * (x % n)) % n;
    }
    else
    {
        long long r = powerMod(x, y / 2, n);
        return ((r % n) * (r % n)) % n;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    long long x, y, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> x >> y >> n;
        cout << powerMod(x, y, n) << '\n';
    }

    return 0;
}
