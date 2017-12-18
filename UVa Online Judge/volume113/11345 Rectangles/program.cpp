// Rectangles
// UVa ID: 11345
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

struct point {
    int x, y;
};

struct rectangle {
    point leftLower, rightTop;
}rs[40];

rectangle getAnd(rectangle r1, rectangle r2)
{
    int lowx = max(r1.leftLower.x, r2.leftLower.x);
    int lowy = max(r1.leftLower.y, r2.leftLower.y);
    int upx = min(r1.rightTop.x, r2.rightTop.x);
    int upy = min(r1.rightTop.y, r2.rightTop.y);
    if (lowx >= upx || lowy >= upy) return rectangle{point{0, 0}, point{0, 0}};
    return rectangle{point{lowx, lowy}, point{upx, upy}}; 
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int m;
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> rs[i].leftLower.x >> rs[i].leftLower.y;
            cin >> rs[i].rightTop.x >> rs[i].rightTop.y;
        }

        rectangle rr = rs[0];
        for (int i = 1; i < m; i++)
        {
            rr = getAnd(rr, rs[i]);
            if (rr.leftLower.x == rr.rightTop.x || rr.leftLower.y == rr.rightTop.y)
                break;
        }

        cout << "Case " << c << ": ";
        cout << abs(rr.leftLower.x - rr.rightTop.x) * abs(rr.leftLower.y - rr.rightTop.y) << '\n';
    }

    return 0;
}
