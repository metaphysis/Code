// Tacos Panchita
// UVa ID: 905
// Verdict: Accepted
// Submission Date: 2017-03-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// The sample output was still wrong.
//

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

struct point
{
    int x, y;
    
    bool operator<(const point &b) const
    {
        if (y != b.y) return y > b.y;
        else return x < b.x;
    }
};

struct line
{
    int a, b, c;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int x, y, w, h, n, p, m;
    int cases = 0;
    line line1, line2;
    
    line1.a = 1, line1.b = -1;
    line2.a = 1; line2.b = 1;
    
    while (cin >> x >> y >> w >> h)
    {
        line1.c = y - x;
        line2.c = -(x + y);
        
        vector<point> movable;
        
        for (int i = h; i >= 1; i--)
        {
            cin >> n;
            for (int j = 1; j <= n; j++)
            {
                cin >> p;
                
                if ((line1.a * p + line1.b * i + line1.c) <= 0 && (line2.a * p + line2.b * i + line2.c) > 0)
                {
                    movable.push_back(point{p, i + 1});
                }
                else if ((line1.a * p + line1.b * i + line1.c) < 0 && (line2.a * p + line2.b * i + line2.c) <= 0)
                {
                    movable.push_back(point{p - 1, i});
                }
                else if((line1.a * p + line1.b * i + line1.c) >= 0 && (line2.a * p + line2.b * i + line2.c) < 0)
                {
                    movable.push_back(point{p, i - 1});
                }
                else
                {
                    movable.push_back(point{p + 1, i});
                }
            }
        }

        sort(movable.begin(), movable.end());
        
        if (cases++ > 0) cout << '\n';
        cout << x << ' ' << y << ' ' << w << ' ' << h << '\n';
        
        int start = -1, end = -1;
        for (int i = h; i >= 1; i--)
        {
            start = -1;
            for (int j = end + 1; j < movable.size(); j++)
            {
                if (movable[j].y == i && movable[j].x >= 1 && movable[j].x <= w)
                {
                    if (start == -1) start = j;
                    end = j;
                }
                else if (movable[j].y < i) break;
            }
            
            if (start == - 1)
            {
                cout << "0\n";
                continue;
            }
            
            cout << (end - start + 1);
            for (int j = start; j <= end; j++)
                cout << ' ' << movable[j].x;
            cout << '\n';
        }
    }
    
    return 0;
}
