// Robot Instructions
// UVa ID: 12503
// Verdict: Accepted
// Submission Date: 2017-12-20
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

    int cases, n, idx, offset[110];
    string action;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int p = 0;
        
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> action;
            if (action == "LEFT")
            {
                offset[i] = -1;
                p -= 1;
            }
            else if (action == "RIGHT")
            {
                offset[i] = 1;
                p += 1;
            }
            else
            {
                cin >> action >> idx;
                offset[i] = offset[idx];
                p += offset[i];
            }
        }
        
        cout << p << '\n';
    }

    return 0;
}
