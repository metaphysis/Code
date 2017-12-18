// The Easiest Way
// UVa ID: 11207
// Verdict: Accepted
// Submission Date: 2017-12-18
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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, w, h;
    
    while (cin >> n, n > 0)
    {
        int idx = 1, largest = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> w >> h;
            if (w < h) swap(w, h);
            
            if (4 * h <= w)
            {
                if (4 * h > largest) largest = 4 * h, idx = i;
            }
            else
            {
                if (w > largest) largest = w, idx = i;
            }
            
            if (2 * min(w, h) > largest) largest = 2 * min(w, h), idx = i;
        }
        cout << idx << '\n';
    }

    return 0;
}
