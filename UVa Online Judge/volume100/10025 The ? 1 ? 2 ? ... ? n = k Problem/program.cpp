// The ? 1 ? 2 ? ... ? n = k Problem
// UVa ID: 10025
// Verdict: Accepted
// Submission Date: 2018-02-28
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

    int cases, k;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> k;
        int x = sqrt(2 * abs(k));
        if (x * (x + 1) / 2 < k) x++;
        if (x == 0) x++;
        while (true)
        {
            int r = x * (x + 1) / 2 - k;
            if (r % 2 == 1) x++;
            else break;
        }
        if (c > 1) cout << '\n';
        cout << x << '\n';
    }

    return 0;
}
