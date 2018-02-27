// Billiard Bounces
// UVa ID: 11130
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

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double a, b, v, A, s;
    while (cin >> a >> b >> v >> A >> s, a > 0)
    {
        double delta = (A / 180.0) * PI;
        double horizontal = v * s / 2.0 * cos(delta);
        double vertical = v * s / 2.0 * sin(delta);
        int cntVertical = 0;
        if (2 * horizontal >= a) cntVertical++;
        if (2 * horizontal - a > 0) cntVertical += (2 * horizontal - a) / (2 * a);
        int cntHorizontal = 0;
        if (2 * vertical >= b) cntHorizontal++;
        if (2 * vertical - b > 0) cntHorizontal += (2 * vertical - b) / (2 * b);
        cout << cntVertical << ' ' << cntHorizontal << '\n';
    }

    return 0;
}
