// Intersecting Circles
// UVa ID: 453
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const double EPSILON = 1e-7;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    double x1, y1, r1, x2, y2, r2;
    
    while (cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2)
    {
        double distances1 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        double distances2 = (r1 + r2) * (r1 + r2);
        
        // same center
        if (distances1 <= EPSILON)
        {
            if (fabs(r1 - r2) <= EPSILON)
                cout << "THE CIRCLES ARE THE SAME\n";
            else
                cout << "NO INTERSECTION\n";
            continue;
        }
        
        // the distance between two circle center bigger than sum of radius
        if (distances1 > distances2 + EPSILON)
        {
            cout << "NO INTERSECTION\n";
            continue;
        }
        
        if (fabs(distance1 - distance2) <= EPSION)
        {
        }
        
        double distances3 = (r1 - r2) * (r1 - r2);
        if (r1 > r2 + EPSILON && distance1 < distances3)
        {
        }
        
    }
    
	return 0;
}
