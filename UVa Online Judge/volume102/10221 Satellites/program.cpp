// Satellites
// UVa ID: 10221
// Verdict: Accepted
// Submission Date: 2017-12-17
// UVa Run Time: 0.000s
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

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout << fixed << setprecision(6);

    double s, a;
    string unit;
    
    while (cin >> s >> a >> unit)
    {
        if (unit == "min") a /= 60;
        if (a > 180.0) a = 360.0 - a;
        a = a / 180.0 * PI;
        double arc = (6440.0 + s) * a;
        double chord = 2 * (6440.0 + s) * sin(a / 2);
        cout << arc << ' ' << chord << '\n';
    }

    return 0;
}
