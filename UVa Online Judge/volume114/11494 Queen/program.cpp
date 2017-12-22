// Queen
// UVa ID: 11494
// Verdict: Accepted
// Submission Date: 2017-12-22
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

    int x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2)
    {
        if (x1 == 0) break;
        
        if (x1 == x2 && y1 == y2) cout << 0 << '\n';
        else
        {
            if (x1 == x2 || y1 == y2 || abs(x1 - x2) == abs(y1 - y2)) cout << 1 << '\n';
            else cout << 2 << '\n';
        }
    }

    return 0;
}
