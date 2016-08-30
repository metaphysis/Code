// Ratio
// UVa ID: 654
// Verdict: Wrong Answer
// Submission Date: 2016-08-30
// UVa Run Time: 0.000s
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

int gcd(int a, int b)
{
    int t;
    while (a % b) t = a, a = b, b = t % b;
    return b;
}

bool better(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
    pair<int, int> e1(abs(a.first * c.second - a.second * c.first), a.second);
    pair<int, int> e2(abs(b.first * c.second - b.second * c.first), b.second);
    
    return e1.first * e2.second <= e2.first * e1.second;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int m, n, cases = 0;
    
    while (cin >> m >> n)
    {
        if (cases++ > 0)
            cout << '\n';

        int g = gcd(m, n);
        if (g > 1)
            m /= g, n /= g;

        pair<int, int> exact(m, n), last(m / n, 1);
        pair<int, int> low(last.first, 1), up(last.first + 1, 1);

        if (better(up, low, exact))
            last.first += 1;
        cout << last.first << '/' << 1 << '\n';

        for (int i = 2; i < n; i++)
        {
            int top = (double)(i * m) / (double)(n);
            int lower = max(0, top - 20), upper = top + 20;
            
            pair<int, int> best = last;
            bool updated = false;
            
            for (int start = lower; start <= upper; start++)
            {
                pair<int, int> candidate(start, i);
                if (better(candidate, best, exact))
                {
                    best = candidate;
                    updated = true;
                }
            }

            if (updated && gcd(best.first, best.second) == 1)
            {
                cout << best.first << '/' << best.second << '\n';
                last = best;
            }
        }

        if (m != n)
            cout << m << '/' << n << '\n';
    }
    
	return 0;
}
