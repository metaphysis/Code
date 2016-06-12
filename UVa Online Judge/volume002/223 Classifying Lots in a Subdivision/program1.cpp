// Classifying Lots in a Subdivision
// UVa IDs: 223
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int MODULUS = 100000;

struct segment
{
    int x1, y1, x2, y2;
};

map<int, set<int> > edges;
vector <segment> boundary;
int minX, minY, maxX, maxY, x1, y1, x2, y2;
int n, cases = 0;

int cross_product(int ax, int ay, int bx, int by, int cx, int cy)
{
	return (cx - ax) * (by - ay) - (bx - ax) * (cy - ay);
}

int cross_product(int a, int b, int c)
{
    return cross_product(a / MODULUS, a % MODULUS, b / MODULUS, b % MODULUS, c / MODULUS, c % MODULUS);
}

int getNextVertices(int first, int second)
{
    int third = -1;
    for (auto it = edges[second].begin(); it != edges[second].end(); it++)
    {
        if (*it == first || *it == second)
            continue;
            
        if (third == -1)
        {
            third = *it;
            continue;
        }
        
        int lastcp = cross_product(first, second, third);
        int currentcp = cross_product(first, second, *it);
        
        if ((currentcp > 0 && lastcp <= 0) || (currentcp == 0 && lastcp < 0) ||
            (currentcp * lastcp > 0 && cross_product(second, third, *it) > 0))
            third = *it;
    }
    return third;
}

int main(int argc, char *argv[])
{
    while (cin >> n, n)
    {
        // read data, find the boundary of rectangle
        boundary.clear();
        minX = 10000, minY = 10000, maxX = 1, maxY = 1;
        for (int i = 1; i <= n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            minX = min(minX, min(x1, x2)), minY = min(minY, min(y1, y2));
            maxX = max(maxX, max(x1, x2)), maxY = max(maxY, max(y1, y2));
            boundary.push_back((segment){x1, y1, x2, y2});
        }

        // add adges
        edges.clear();
        for (int i = 0; i < boundary.size(); i++)
        {
            int start = boundary[i].x1 * MODULUS + boundary[i].y1;
            int end = boundary[i].x2 * MODULUS + boundary[i].y2;
            edges[start].insert(end), edges[end].insert(start);
        }
        
        // remove line segment which is not boundary of subdivision
        for (int i = boundary.size() - 1; i >= 0; i--)
        {
            if ((boundary[i].x1 == minX && boundary[i].x2 == minX) || 
                (boundary[i].x1 == maxX && boundary[i].x2 == maxX) ||
                (boundary[i].y1 == minY && boundary[i].y2 == minY) ||
                (boundary[i].y1 == maxY && boundary[i].y2 == maxY))
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
            x1 = boundary.front().x1, y1 = boundary.front().y1;
            x2 = boundary.front().x2, y2 = boundary.front().y2;
            
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
                int third = getNextVertices(first, second);
                vertices.push_back(third);
                if (third == vertices.front())
                    break;    
                first = second, second = third;
            }
            
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
