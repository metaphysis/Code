// Euclid
// UVa ID: 1249
// Verdict: Accepted
// Submission Date: 2017-03-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # eyah dot net

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
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    double ax, ay, bx, by, cx, cy, dx, dy, ex, ey, fx, fy;
    double hx, hy, gx, gy;
    
    cout.setf(ios::fixed);
    cout.precision(3);
    
    while (true)
    {
        cin >> ax >> ay >> bx >> by >> cx >> cy;
        cin >> dx >> dy >> ex >> ey >> fx >> fy;
        
        if (ax == 0.0 && ay == 0.0 && bx == 0.0 && by == 0.0 && cx == 0.0 && cy == 0.0)
            break;
            
        double triangle = abs(dx * ey - dy * ex + ex * fy - ey * fx + fx * dy - fy * dx) / 2.0;
        double distAB = sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
        double height = triangle / distAB;
        double distAC = sqrt(pow(ax - cx, 2) + pow(ay - cy, 2));
        double distBC = sqrt(pow(bx - cx, 2) + pow(by - cy, 2));
        double angleCAB = acos((distAC * distAC + distAB * distAB - distBC * distBC) / (2.0 * distAC * distAB));
        double distAH = height / sin(angleCAB);
        
        hx = ax + (cx - ax) * distAH / distAC;
        hy = ay + (cy - ay) * distAH / distAC;
        
        gx = bx + (hx - ax);
        gy = by + (hy - ay);
        
        cout << gx << ' ' << gy << ' ' << hx << ' ' << hy << '\n';
    }
    
    return 0;
}
