// Watching Watches
// UVa ID: 10339
// Verdict: Accepted
// Submission Date: 2018-01-04
// UVa Run Time: 0.020s
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

    int k, m;
    while (cin >> k >> m)
    {
        double secondsElapsed = fmod(43200.0 / abs(k - m) * (86400.0 - k), 86400.0);
        int hours = secondsElapsed / 3600;
        int minutes = fmod(secondsElapsed, 3600) / 60 + 0.5;
        if (minutes == 60) hours++, minutes = 0;
        if ((hours = hours % 12) == 0) hours = 12;
        cout << k << ' ' << m << ' ';
        cout << setw(2) << setfill('0') << hours << ':';
        cout << setw(2) << setfill('0') << minutes << '\n';
    }

    return 0;
}
