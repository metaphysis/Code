// Simple Equations
// UVa ID: 11565
// Verdict: Accepted
// Submission Date: 2017-11-09
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

    int cases, a, b, c;
    
    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> a >> b >> c;
        
        int lowx = sqrt(c) + 1, flag = 0;
        for (int x = -lowx; x <= lowx; x++)
            for (int y = x + 1; y <= lowx; y++)
            {
                int z = a - x - y;
                if (z <= y || z > lowx) continue;
                if (x * y * z != b) continue;
                if (x * x + y * y + z * z != c) continue;
                cout << x << ' ' << y << ' ' << z << '\n';
                flag = 1;
                goto print;
            }
                
        print:
        if (!flag) cout << "No solution.\n";
    }

    return 0;
}
