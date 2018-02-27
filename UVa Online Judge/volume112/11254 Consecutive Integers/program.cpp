// Consecutive Integers
// UVa ID: 11254
// Verdict: Accepted
// Submission Date: 2018-02-27
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

    int n;
    while (cin >> n, n > 0)
    {
        int x = sqrt(2 * n);
        if (x * (x + 1) / 2 < n) x++;
        if (x * (x + 1) / 2 == n)
        {
            cout << n << " = 1 + ... + " << x << '\n';
            continue;
        }
        for (int i = x - 1; i >= 1; i--)
        {
            if ((n - i * (i + 1) / 2) % i == 0)
            {
                int r = (n - i * (i + 1) / 2) / i;
                cout << n << " = " << (1 + r) << " + ... + " << (i + r) << '\n';
                break;
            }
        }
    }

    return 0;
}
