// Logarithms
// UVa ID: 11666
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.010s
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

    int n;
    while (cin >> n, n > 0)
    {
        double e = exp(1);
        for (int L = 0; ; L++)
        {
            double x = fabs(1.0 - n / exp(L));
            if (x < 1.0)
            {
                cout << L << ' ';
                x = 1.0 - n / exp(L);
                cout << fixed << setprecision(8) << x << '\n';
                break;
            }
        }
    }

    return 0;
}
