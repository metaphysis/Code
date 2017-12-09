// The Other Two Trees
// UVa ID: 10250
// Verdict: Accepted
// Submission Date: 2017-12-09
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

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);

    double x1, y1, x2, y2;
    double ax1, ay1, ax2, ay2;

    while (cin >> x1 >> y1 >> x2 >> y2)
    {
        double d = sqrt((pow(x1 - x2, 2) + pow(y1 - y2, 2)) / 2);

        double at1 = atan2(y2 - y1, x2 - x1);
        at1 += PI / 4;
        ax1 = x1 + d * cos(at1), ay1 = y1 + d * sin(at1);
        
        double at2 = atan2(y1 - y2, x1 - x2);
        at2 += PI / 4;
        ax2 = x2 + d * cos(at2), ay2 = y2 + d * sin(at2);

        cout << ax1 << ' ' << ay1 << ' ' << ax2 << ' ' << ay2 << '\n';
    }

    return 0;
}
