// Necklace
// UVa ID: 11001
// Verdict: Accepted
// Submission Date: 2017-11-07
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

const double EPSILON = 1e-7;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int vt, v0;
    double diameter[60010];
    
    while (cin >> vt >> v0, vt > 0)
    {
        int k = vt / v0;

        if ((vt % v0) == 0) k--;

        double longest = 0.0;
        for (int i = 1; i <= k; i++)
        {
            double v = (double)vt / i;
            
            diameter[i] = i * 0.3 * sqrt(v - v0);
            if (diameter[i] > longest + EPSILON)
                longest = diameter[i];
        }
        
        int cnt = 0, disc = 0;
        for (int i = 1; i <= k; i++)
        {
            if (fabs(longest - diameter[i]) <= EPSILON)
            {
                cnt++;
                disc = i;
            }
            if (cnt > 1) break;
        }
        
        if (cnt == 1) cout << disc << '\n';
        else cout << "0\n";
    }
    
    return 0;
}
