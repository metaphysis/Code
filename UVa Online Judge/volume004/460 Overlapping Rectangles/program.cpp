// Overlapping Rectangles
// UVa ID: 460
// Verdict: Accepted
// Submission Date: 2016-07-17
// UVa Run Time: 0.000s
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    int x1, y1, x2, y2, x3, y3, x4, y4;
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << '\n';
        
        cin >> x1 >> y1 >> x2 >> y2;
        cin >> x3 >> y3 >> x4 >> y4;
        
        int lowx = max(x1, x3), lowy = max(y1, y3), upx = min(x2, x4), upy = min(y2, y4);
        if (lowx >= upx || lowy >= upy)
            cout << "No Overlap\n";
        else
            cout << lowx << ' ' << lowy << ' ' << upx << ' ' << upy << '\n';
    }
    
	return 0;
}
