// Harmonic Mean
// UVa ID: 12068
// Verdict: Accepted
// Submission Date: 2018-03-08
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

    int cases, n;
    long long up, down, next;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> down;
        up = 1;
        for (int i = 1; i < n; i++)
        {
            cin >> next;
            up = up * next + down;
            down *= next;
            long long g = __gcd(up, down);
            if (g > 1) up /= g, down /= g;
        }
        down *= n;
        long long g = __gcd(up, down);
        if (g > 1) up /= g, down /= g;
        cout << "Case " << c << ": " << down << '/' << up << '\n';
    }

    return 0;
}
