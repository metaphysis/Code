// Supermean
// UVa ID: 10883
// Verdict: Accepted
// Submission Date: 2017-08-26
// UVa Run Time: 0.060s
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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;

    cin >> cases;
    for (int i = 1; i <= cases; i++)
    {
        double c = 0.0, di, mean = 0.0;

        cin >> n;
        for (int j = 1; j <= n; j++)
        {
            cin >> di;
            if (j > 1) c += log2((double)(n - j + 1) / (j - 1));
            if (fabs(di) > 0)
            {
                double sign = (di > 0 ? 1.0 : -1.0);
                mean += sign * pow(2, c + log2(fabs(di)) - (n - 1));
            }
        }

        cout << "Case #" << i << ": ";
        cout << fixed << setprecision(3) << mean << '\n';
    }

    return 0;
}
