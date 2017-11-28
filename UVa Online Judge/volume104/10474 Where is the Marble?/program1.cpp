// Where is the Marble?
// UVa ID: 10474
// Verdict: Accepted
// Submission Date: 2017-11-28
// UVa Run Time: 0.050s
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

    int n, q, cases = 0;
    int numbers[1000010];

    while (cin >> n >> q)
    {
        if (n == 0 && q == 0) break;

        for (int i = 0; i < n; i++)
            cin >> numbers[i];
        sort(numbers, numbers + n);

        cout << "CASE# " << ++cases << ":\n";
        for (int i = 1, j, k; i <= q; i++)
        {
            cin >> j;

            int left = -1, right = n, middle;
            while ((left + 1) != right)
            {
                middle = left + (right - left) / 2;
                if (numbers[middle] < j) left = middle;
                else right = middle;
            }
            if (right >= n || numbers[right] != j) right = -1;
            if (right >= 0) cout << j << " found at " << right + 1 << '\n';
            else cout << j << " not found\n";
        }
    }

    return 0;
}
