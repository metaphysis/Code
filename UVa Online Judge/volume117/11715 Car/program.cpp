// Car
// UVa ID: 11715
// Verdict: Accepted
// Submission Date: 2018-03-05
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

    int category, cases = 0;
    double u, v, a, t, s;

    cout.setf(ios::fixed);
    cout.precision(3);

    while (cin >> category, category > 0)
    {
        cout << "Case " << ++cases << ": ";
 
        if (category == 1)
        {
            // u v t are given then print s and a
            cin >> u >> v >> t;
            a = (v - u) / t;
            s = u * t + 0.5 * a * t * t;
            cout << s << ' ' << a << '\n';
        }
        else if (category == 2)
        {
            // u v a are given then print s and t
            cin >> u >> v >> a;
            t = (v - u) / a;
            s = u * t + 0.5 * a * t * t;
            cout << s << ' ' << t << '\n';
        }
        else if (category == 3)
        {
            // u a s are given then print v and t
            cin >> u >> a >> s;
            t = (-u + sqrt(u * u + 2.0 * a * s)) / a;
            v = u + a * t;
            cout << v << ' ' << t << '\n';
        }
        else
        {
            // v a s are given then print u and t
            cin >> v >> a >> s;
            double root = sqrt(v * v - 2.0 * a * s);
            double t1 = (v + root) / a;
            double t2 = (v - root) / a;
            if (t2 < 0) t = t1;
            else
            {
                u = v - a * t1;
                if (u < 0) t = t2;
                else t = t1;
            }
            u = v - a * t;
            cout << u << ' ' << t << '\n';
        }
    }

    return 0;
}
