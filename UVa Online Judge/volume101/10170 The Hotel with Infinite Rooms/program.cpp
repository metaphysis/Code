// The Hotel with Infinite Rooms
// UVa ID: 10170
// Verdict: Accepted
// Submission Date: 2018-03-01
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

    long long S, D;
    while (cin >> S >> D)
    {
        long long low = 1, high = sqrt(2 * D), middle;
        while (low <= high)
        {
            middle = (low + high) / 2;
            if ((S + S + middle - 1) * middle / 2 < D)
                low = middle + 1;
            else
                high = middle - 1;
        }
        cout << (S + low - 1) << '\n';
    }

    return 0;
}
