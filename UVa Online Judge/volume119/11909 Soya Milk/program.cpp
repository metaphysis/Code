// Soya Milk
// UVa ID: 11909
// Verdict: Accepted
// Submission Date: 2017-12-15
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
    cout << fixed << setprecision(3);

    double l, w, h, a;
    
    while (cin >> l >> w >> h >> a)
    {
        double total = l * w * h;
        a = a / 180.0 * PI;
        double hh = l * tan(a);
        if (hh > h)
        {
            a = PI / 2.0 - a;
            double remain = h * h * tan(a) * w / 2;
            cout << remain << " mL\n";
        }
        else
        {
            double out = l * l * tan(a) * w / 2;
            cout << (total - out) << " mL\n";
        }
    }

    return 0;
}
