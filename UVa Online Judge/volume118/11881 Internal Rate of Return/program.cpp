// Internal Rate of Return
// UVa ID: 11881
// Verdict: Accepted
// Submission Date: 2017-11-29
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

const double EPSILON = 1e-8;

int n;
double f[12];

double eval(double x)
{
    double s = 0.0, t = 1.0;
    for (int i = n; i >= 0; i--)
    {
        s += t * f[i];
        t *= (1.0 + x);
    }
    return s;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    while (cin >> n, n > 0)
    {
        for (int i = 0; i <= n; i++)
            cin >> f[i];
        
        double irr = 0.0, v = eval(irr);
        if (abs(v) < EPSILON) cout << "0.00\n";
        else
        {
            double left = 0, right = 10000, middle, temp;
            if (v < 0) left = -1, right = 0;
            for (int i = 1; i <= 50; i++)
            {
                middle = (left + right) / 2.0;
                temp = eval(middle);
                if (abs(temp) < EPSILON) break;
                if (temp < 0) right = middle;
                else left = middle;
            }
            cout << fixed << setprecision(2) << middle << '\n';
        }
    }

    return 0;
}
