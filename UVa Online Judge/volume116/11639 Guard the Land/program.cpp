// Guard the Land
// UVa ID: 11639
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
};

rectangle getAnd(rectangle r1, rectangle r2)
{
    int lowy = max(r1.leftLower.y, r2.leftLower.y);
    int rightx = min(r1.rightTop.x, r2.rightTop.x);
    int upy = min(r1.rightTop.y, r2.rightTop.y);
    int leftx = max(r1.leftLower.x, r2.leftLower.x);
    
    if (lowy >= upy || leftx >= rightx) return rectangle{point{0, 0}, point{0, 0}};
    
    return rectangle{point{leftx, lowy}, point{rightx, upy}}; 
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        rectangle r1, r2;

        cin >> r1.leftLower.x >> r1.leftLower.y;
        cin >> r1.rightTop.x >> r1.rightTop.y;
        cin >> r2.leftLower.x >> r2.leftLower.y;
        cin >> r2.rightTop.x >> r2.rightTop.y;

        rectangle rr = getAnd(r1, r2);

        int all = 10000;
        int strongly = abs(rr.leftLower.x - rr.rightTop.x) * abs(rr.leftLower.y - rr.rightTop.y);
        int weak = abs(r1.leftLower.x - r1.rightTop.x) * abs(r1.leftLower.y - r1.rightTop.y);
        weak += abs(r2.leftLower.x - r2.rightTop.x) * abs(r2.leftLower.y - r2.rightTop.y);
        weak -= 2 * strongly;
        
        cout << "Night " << c << ": ";
        cout << strongly << ' ' << weak << ' ' << (all - strongly - weak) << '\n';
    }

    return 0;
}
