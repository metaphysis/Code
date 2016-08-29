// Sorting Slides
// UVa ID: 663
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

struct point
{
    int x, y;
};

struct rectangle
{
    int xmin, xmax, ymin, ymax;
};

rectangle rectangles[30];
point points[30];

bool pointInBox(point &p, rectangle &r)
{
    return p.x > r.xmin && p.x < r.xmax && p.y > r.ymin && p.y < r.ymax;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int heap, cases = 0;
    while (cin >> heap, heap)
    { 
        cout << "Heap " << ++cases << '\n';
        
        for (int i = 1; i <= heap; i++)
            cin >> rectangles[i].xmin >> rectangles[i].xmax >> rectangles[i].ymin >> rectangles[i].ymax;
        for (int i = 1; i <= heap; i++)
            cin >> points[i].x >> points[i].y;
            
        int r_matched[30], p_matched[30], r_unmatched = heap;
        int inside[30][30];
        
        memset(inside, 0, sizeof(inside));
        for (int i = 1; i <= heap; i++)
            for (int j = 1; j <= heap; j++)
                inside[i][j] = pointInBox(points[i], rectangles[j]) ? 1 : 0;
        
        memset(r_matched, 0, sizeof(r_matched));
        memset(p_matched, 0, sizeof(p_matched));
        
        while (true)
        {
            bool updated = false;
            
            for (int i = 1; i <= heap; i++)
                if (r_matched[i] == 0)
                {
                    int only = 0, tag = 0;
                    for (int j = 1; j <= heap; j++)
                    {
                        if (p_matched[j] == 0 && inside[j][i])
                        {
                            only++;
                            tag = j;
                        }
                    }
                    
                    if (only == 1)
                    {
                        updated = true;
                        r_matched[i] = tag;
                        p_matched[tag] = 1;
                        r_unmatched--;
                    }
                }
            
            for (int i = 1; i <= heap; i++)
                if (p_matched[i] == 0)
                {
                    int only = 0, tag = 0;
                    for (int j = 1; j <= heap; j++)
                    {
                        if (r_matched[j] == 0 && inside[i][j])
                        {
                            only++;
                            tag = j;
                        }
                    }
                    
                    if (only == 1)
                    {
                        updated = true;
                        r_matched[tag] = i;
                        p_matched[i] = 1;
                        r_unmatched--;
                    }
                }

            if (updated == false)
                break;
        }
        
        if (r_unmatched == heap)
            cout << "none\n";
        else
        {
            bool outputed = false;
            for (int i = 1; i <= heap; i++)
                if (r_matched[i] > 0)
                {
                    if (outputed)
                        cout << ' ';
                    else
                        outputed = true;
                    cout << '(' << (char)('A' + i - 1) << ',' << r_matched[i] << ')';
                }
            cout << '\n';
        }
        
        cout << '\n';
    }
    
	return 0;
}
