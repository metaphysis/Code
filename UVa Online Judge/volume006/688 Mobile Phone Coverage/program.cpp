// Mobile Phone Coverage
// UVa ID: 688
// Verdict: Accepted
// Submission Date: 2017-06-06
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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    double area, x[105], y[105], r[105], dx[105 * 2], dy[105 * 2];
    
    int cases = 0;
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> x[i] >> y[i] >> r[i];
            dx[i * 2] = x[i] - r[i], dx[i * 2 + 1] = x[i] + r[i];
            dy[i * 2] = y[i] - r[i], dy[i * 2 + 1] = y[i] + r[i];
        }
        
        sort(dx, dx + 2 * n);
        sort(dy, dy + 2 * n);
        
        double area = 0.0;
        for (int i = 1; i < 2 * n; i++)
            for (int j = 1; j < 2 * n; j++)
                for (int k = 0; k < n; k++)
                {
                    if (dx[i - 1] >= x[k] - r[k] && dx[i] <= x[k] + r[k])
                        if (dy[j - 1] >= y[k] - r[k] && dy[j] <= y[k] + r[k])
                        {
                            area += (dx[i] - dx[i - 1]) * (dy[j] - dy[j - 1]);
                            break;
                        }
                }

        cout << ++cases << ' ' << fixed << setprecision(2) << area << '\n';
    }
    return 0;
}
