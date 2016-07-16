// Classifying Lots in a Subdivision
// UVa ID: 223
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const int MODULUS = 100000;

struct segment
{
    int x1, y1, x2, y2;
};

map<int, set<int> > edges;
vector <segment> boundary;
int minX, minY, maxX, maxY;

// cross product
int cp(int ax, int ay, int bx, int by, int cx, int cy)
{
	return (cx - ax) * (by - ay) - (bx - ax) * (cy - ay);
}

int cp(int a, int b, int c)
{
    return cp(a / MODULUS, a % MODULUS, b / MODULUS, b % MODULUS, c / MODULUS, c % MODULUS);
}

int getNextVertices(int first, int second)
{
    int third = -1;
    for (auto it = edges[second].begin(); it != edges[second].end(); it++)
    {
        //cout << "candidate: " << *it / 100 << " " << *it % 100 << endl;
        
        if (*it == first || *it == second)
            continue;
            
        if (third == -1)
        {
            third = *it;
            continue;
        }
        
        int lastcp = cp(first, second, third);
        int currentcp = cp(first, second, *it);
        
        if (lastcp == 0 && currentcp == 0)
        {
            assert(false);
        }
        
        if ((currentcp > 0 && lastcp <= 0) || (currentcp == 0 && lastcp < 0))
        {
            third = *it;
        }
        else if (currentcp * lastcp > 0)
        {
            if (cp(second, third, *it) > 0)
                third = *it;
        }
    }
    return third;
}

bool pointInBox(int x, int y, int startx, int starty, int endx, int endy)
{
    return min(startx, endx) <= x && x <= max(startx, endx) && min(starty, endy) <= y && y <= max(starty, endy);
}

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n)
    {
        vector <segment> pool;

        // read data, find the boundary of rectangle
        minX = 10000, minY = 10000, maxX = 0, maxY = 0;
        
        int x1, y1, x2, y2;
        for (int i = 1; i <= n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            
            minX = min(minX, min(x1, x2)), minY = min(minY, min(y1, y2));
            maxX = max(maxX, max(x1, x2)), maxY = max(maxY, max(y1, y2));
            
            if (x1 > x2 || (x1 == x2 && y1 > y2))
                swap(x1, x2), swap(y1, y2);
                
            pool.push_back((segment){x1, y1, x2, y2});
        }
        
        // remove the overlapped segment
        boundary.clear();
        
        while (pool.size() > 0)
        {   
            segment s1 = pool.front();
            
            int removed = -1;
            for (int i = 1; i < pool.size(); i++)
            {
                segment s2 = pool[i];
                
                // colinear
                if (cp(s1.x1, s1.y1, s1.x2, s1.y2, s2.x1, s2.y1) == 0 && cp(s1.x1, s1.y1, s1.x2, s1.y2, s2.x2, s2.y2) == 0)
                {
                    if (pointInBox(s1.x1, s1.y1, s2.x1, s2.y1, s2.x2, s2.y2) && pointInBox(s1.x2, s1.y2, s2.x1, s2.y1, s2.x2, s2.y2))
                    {
                        removed = i;
                        break;
                    }
                    
                    if (pointInBox(s2.x1, s2.y1, s1.x1, s1.y1, s1.x2, s1.y2) && pointInBox(s2.x2, s2.y2, s1.x1, s1.y1, s1.x2, s1.y2))
                    {
                        removed = 0;
                        break;
                    }
                }
            }
            
            if (removed >= 0)
            {
                pool.erase(pool.begin() + removed);
                assert(false);
            }
            else
            {
                boundary.push_back(s1);
                pool.erase(pool.begin());
            }
        }
        
        // add adges
        edges.clear();
        for (int i = 0; i < boundary.size(); i++)
        {
            int start = boundary[i].x1 * MODULUS + boundary[i].y1;
            int end = boundary[i].x2 * MODULUS + boundary[i].y2;
            edges[start].insert(end), edges[end].insert(start);
            
            //cout << "start = " << start << " " << edges[start].size() << endl;
            //cout << "end = " << end << " " << edges[end].size() << endl;
        }
        
        // remove line segment which is not boundary of subdivision
        for (int i = boundary.size() - 1; i >= 0; i--)
        {
            if (boundary[i].x1 == minX && boundary[i].x2 == minX)
                continue;
            if (boundary[i].x1 == maxX && boundary[i].x2 == maxX)
                continue;
            if (boundary[i].y1 == minY && boundary[i].y2 == minY)
                continue;
            if (boundary[i].y1 == maxY && boundary[i].y2 == maxY)
                continue;
            boundary.erase(boundary.begin() + i);
        }
        
        // find lot
        int lots = 0;
        map <int, int> counter;
        
        while (boundary.size())
        {
            // get the start edge
            int startx, starty, nextx, nexty;
            x1 = boundary[0].x1, y1 = boundary[0].y1, x2 = boundary[0].x2, y2 = boundary[0].y2;
            
            if (x1 == x2 && x1 == minX)
            {
                startx = x1, starty = min(y1, y2);
                nextx = x1, nexty = max(y1, y2);
            }
            else if (x1 == x2 && x1 == maxX)
            {
                startx = x1, starty = max(y1, y2);
                nextx = x1, nexty = min(y1, y2);
            }
            else if (y1 == y2 && y1 == minY)
            {
                startx = max(x1, x2), starty = y1;
                nextx = min(x1, x2), nexty = y1;
            }
            else if (y1 == y2 && y1 == maxY)
            {
                startx = min(x1, x2), starty = y1;
                nextx = max(x1, x2), nexty = y1;
            }
            
            // start find polygon in clockwise
            vector<int> vertices;
            int first = startx * MODULUS + starty, second = nextx * MODULUS + nexty;
            vertices.push_back(first), vertices.push_back(second);
            
            while (true)
            {
                //cout << "first: " << first / 100 << " " << first % 100 << endl;
                //cout << "second: " << second / 100 << " " << second % 100 << endl;
                
                int third = getNextVertices(first, second);
                vertices.push_back(third);
                
                //cout << "third: " << third / 100 << " " << third % 100 << endl;
                
                if (third == vertices.front())
                    break;
                        
                first = second, second = third;
            }
            
            //cout << "process end." << endl;
            
            // remove the used boundary
            for (int i = 0; i < vertices.size() - 1; i++)
                for (int j = boundary.size() - 1; j >= 0; j--)
                {
                    int start = boundary[j].x1 * MODULUS + boundary[j].y1;
                    int next = boundary[j].x2 * MODULUS + boundary[j].y2;
                    
                    if ((vertices[i] == start && vertices[i + 1] == next) || (vertices[i] == next && vertices[i + 1] == start))
                            boundary.erase(boundary.begin() + j);
                }
            
            counter[vertices.size() - 1]++;
            lots++;
        }
        
        // output the result
        if (cases)
            cout << endl;
            
        cout << "Case " << ++cases << endl;
        
        for (auto it = counter.begin(); it != counter.end(); it++)
        {
            cout << "Number of lots with perimeter consisting of ";
            cout << (*it).first;
            cout << " surveyor's lines = ";
            cout << (*it).second << endl;
        }
        
        cout << "Total number of lots = " << lots << endl;
    }
    
	return 0;
}
