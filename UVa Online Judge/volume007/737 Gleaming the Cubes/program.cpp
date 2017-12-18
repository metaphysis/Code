// Gleaming the Cubes
// UVa ID: 737
// Verdict: Accepted
// Submission Date: 2017-12-18
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

struct point {
    int x, y;
};

struct rectangle {
    point leftLower, rightTop;
    int valid;
};

struct cube {
    int x, y, z, l, w, h;
};

rectangle getAnd(rectangle r1, rectangle r2)
{
    int lowx = max(r1.leftLower.x, r2.leftLower.x);
    int lowy = max(r1.leftLower.y, r2.leftLower.y);
    int upx = min(r1.rightTop.x, r2.rightTop.x);
    int upy = min(r1.rightTop.y, r2.rightTop.y);
    if (lowx >= upx || lowy >= upy) return rectangle{point{0, 0}, point{0, 0}, 0};
    return rectangle{point{lowx, lowy}, point{upx, upy}, 1}; 
}

cube getAnd(cube c1, cube c2)
{
    rectangle r1, r2;

    r1.leftLower.x = c1.x, r1.leftLower.y = c1.z;
    r1.rightTop.x = c1.x + c1.l, r1.rightTop.y = c1.z + c1.h;
    
    r2.leftLower.x = c2.x, r2.leftLower.y = c2.z;
    r2.rightTop.x = c2.x + c2.l, r2.rightTop.y = c2.z + c2.h;
    
    rectangle front = getAnd(r1, r2);
    if (front.valid == 0) return cube{0, 0, 0, 0, 0, 0};

    //cout << front.leftLower.x << ' ' << front.leftLower.y << ' ' << front.rightTop.x << ' ' << front.rightTop.y << '\n';

    r1.leftLower.x = -c1.y - c1.w, r1.leftLower.y = c1.z;
    r1.rightTop.x = -c1.y, r1.rightTop.y = c1.z + c1.h;
    
    r2.leftLower.x = -c2.y - c2.w, r2.leftLower.y = c2.z;
    r2.rightTop.x = -c2.y, r2.rightTop.y = c2.z + c2.h;
    
    rectangle left = getAnd(r1, r2);
    if (left.valid == 0) return cube{0, 0, 0, 0, 0, 0};
    
    //cout << left.leftLower.x << ' ' << left.leftLower.y << ' ' << left.rightTop.x << ' ' << left.rightTop.y << '\n';
    
    return cube{
        front.leftLower.x,
        -left.rightTop.x, 
        front.leftLower.y,
        front.rightTop.x - front.leftLower.x,
        left.rightTop.x - left.leftLower.x ,
        front.rightTop.y - front.leftLower.y
    };
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        cube cr, ci;
        
        cin >> cr.x >> cr.y >> cr.z >> cr.l;
        cr.w = cr.h = cr.l;

        for (int i = 2; i <= n; i++)
        {
            cin >> ci.x >> ci.y >> ci.z >> ci.l;
            ci.w = ci.h = ci.l;

            if (cr.l == 0 || cr.w == 0 || cr.h == 0) continue;
            cr = getAnd(cr, ci);
        }
        cout << cr.l * cr.w * cr.h << '\n';
    }

	return 0;
}
