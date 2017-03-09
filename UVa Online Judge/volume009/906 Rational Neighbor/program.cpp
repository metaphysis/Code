// Rational Neighbor
// UVa ID: 906
// Verdict: Accepted
// Submission Date: 2017-03-10
// UVa Run Time: 0.010s
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
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long a, b;
    double eps;
    
    while (cin >> a >> b >> eps)
    {
        long double t1 = (long double)a / b, t2;
        for (long long d = 1, c; ; d++)
        {
            c = (long long)(t1 * d);
            while (a * d >= b * c) c++;
            
            t2 = (long double)c / d;
            if (t2 - t1 <= eps)
            {
                cout << c << ' ' << d << '\n';
                break;
            }
        }
    }
    
    return 0;
}
