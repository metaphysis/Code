// Watching Watches
// UVa ID: 10339
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
        int diff = abs(k - m);

        double day = 43200.0 / diff;
        double second = 43200.0 - fmod(day * k, 43200.0);
        int hour = second / 3600;
        second = fmod(second, 3600);
        int mm = second / 60 + 0.5;
        if (hour == 0) hour = 12;

        cout << k << ' ' << m << ' ';
        cout << setw(2) << setfill('0') << hour << ':';
        cout << setw(2) << setfill('0') << mm << '\n';
    }

    return 0;
}
