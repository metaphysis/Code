// Medians
// UVa ID: 10347
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

int main(int argc, char *argv[])
{
    double a, b, c;
    while (cin >> a >> b >> c)
    {
        if (a + b <= c || b + c <= a || c + a <= b)
        {
            cout << "-1.000\n";
            continue;
        }
        a = a * 2 / 3, b = b * 2 / 3, c = c * 2 / 3;
        double p = (a + b + c) / 2;
        double area = 3 *  sqrt(p * (p - a) * (p - b) * (p - c));
        cout << fixed << setprecision(3) << area << '\n';
    }

    return 0;
}
