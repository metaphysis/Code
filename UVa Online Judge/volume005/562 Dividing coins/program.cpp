// Dividing coins
// UVa ID: 562
// Verdict: Accepted
// Submission Date: 2016-08-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int coins[110], cents[25010], n, m;

    cin >> n;
    for (int c = 1; c <= n; c++)
    {
        int total = 0;

        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> coins[i];
            total += coins[i];
        }

        if (m <= 1)
        {
            cout << total << '\n';
            continue;
        }

        int half = total / 2;

        memset(cents, 0, sizeof(cents)); 

        for (int i = 1; i <= m; i++)
            for (int j = half; j >= coins[i]; j--)
                cents[j] = max(cents[j], cents[j - coins[i]] + coins[i]);

        for (int i = half; i >= 1; i--)
            if (cents[i])
            {
                cout << abs(total - 2 * cents[i]) << '\n';
                break;
            }
    }

	return 0;
}
