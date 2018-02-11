// Parallelepiped Walk
// UVa ID: 503
// Verdict: Accepted
// Submission Date: 2017-04-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// The solutions below is based on the standard solution which written by Pascal.

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

int curve;

void rotate(int i, int j, int x, int y, int z, int x0, int y0, int L, int W, int H)
{
    if (z == 0)
        curve = min(curve, x * x + y * y);
    else
    {
        if ((i >= 0) && (i < 2))
            rotate(i + 1, j, x0 + L + z, y, x0 + L - x, x0 + L, y0, H, W, L);
        if ((j >= 0) && (j < 2))
            rotate(i, j + 1, x, y0 + W + z, y0 + W - y, x0, y0 + W, L, H, W);
        if ((i <= 0) && (i > -2))
            rotate(i - 1, j, x0 - z, y, x - x0, x0 - H, y0, H, W, L);
        if ((j <= 0) && (j > -2))
            rotate(i, j - 1, x, y0 - z, y - y0, x0, y0 - H, L, H, W);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int L, W, H, x1, y1, z1, x2, y2, z2;

    while (cin >> L >> W >> H >> x1 >> y1 >> z1 >> x2 >> y2 >> z2)
    {
        if (z1 != 0 && z1 != H)
        {
            if (y1 == 0 || y1 == W)
                swap(y1, z1), swap(y2, z2), swap(W, H);
            else
                swap(x1, z1), swap(x2, z2), swap(L, H);
        }
        if (z1 == H)
            z1 = 0, z2 = H - z2;

        curve = numeric_limits<int>::max();
        rotate(0, 0, x2 - x1, y2 - y1, z2, -x1, -y1, L, W, H);
        cout << curve << '\n';
    }

    return 0;
}
