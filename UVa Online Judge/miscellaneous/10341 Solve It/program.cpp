// Solve It
// UVa ID: 10341
// Verdict: Accepted
// Submission Date: 2016-12-20
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

double p, q, r, s, t, u;

// 得到方程的值。
double getValue(double x)
{
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> p >> q >> r >> s >> t >> u)
    {
        double left = 0.0, right = 1.0, middle;

        // 迭代最多40次，精度已经足够。
        for (int i = 1; i <= 40; i++)
        {
            middle = (left + right) / 2.0;
            if (getValue(middle) > 0.0) left = middle;
            else right = middle;
        }

        // 检查解是否满足精度要求。
        if (fabs(getValue(middle)) > 1e-8) cout << "No solution\n";
        else cout << fixed << setprecision(4) << middle << '\n';
    }

	return 0;
}
