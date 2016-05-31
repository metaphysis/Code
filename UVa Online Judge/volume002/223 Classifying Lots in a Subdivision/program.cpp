// Classifying Lots in a Subdivision
// UVa IDs: 223
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct segment
{
    int x1, y1, x2, y2;
};

map<int, set<int> > edges;
vector <segment> boundary;
int minX, minY, maxX, maxY;

// cross product
int cp(int a, int b, int c)
{
	return (c / 100 - a / 100) * (b % 100 - a % 100) -
	    (b / 100 - a / 100) * (c % 100 - a % 100);
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

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n)
    {
        boundary.clear();
        edges.clear();
        
        // read data, find the boundary of rectangle
        minX = 10000, minY = 10000, maxX = 0, maxY = 0;
        
        int x1, y1, x2, y2;
        for (int i = 1; i <= n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            
            minX = min(minX, min(x1, x2));
            minY = min(minY, min(y1, y2));
            maxX = max(maxX, max(x1, x2));
            maxY = max(maxY, max(y1, y2));
            
            if (x1 > x2 || (x1 == x2 && y1 > y2))
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;
                
                temp = y1;
                y1 = y2;
                y2 = temp;
            }

            boundary.push_back((segment){x1, y1, x2, y2});
        }
        
        while (true)
        {   
            bool found = false;
            for (int i = 0; i < boundary.size(); i++)
            {
                for (int j = 0; j < boundary.size(); j++)
                {
                    if (i != j)
                    {
                        if (boundary[i].x1 == boundary[j].x1 && boundary[i].y1 == boundary[j].y1)
                        {
                            if (cp(boundary[i].x1 * 100 + boundary[i].y1, boundary[i].x2 * 100 + boundary[i].y2, boundary[j].x2 * 100 + boundary[j].y2) == 0)
                            {
                                found = true;
                                
                                int distance1 = pow(boundary[i].x2 - boundary[i].x1, 2) + pow(boundary[i].y2 - boundary[i].y1, 2);
                                int distance2 = pow(boundary[j].x2 - boundary[i].x1, 2) + pow(boundary[j].y2 - boundary[i].y1, 2);
                                
                                if (distance1 < distance2)
                                    boundary.erase(boundary.begin() + j);
                                else
                                    boundary.erase(boundary.begin() + i);
                                
                                break;
                            }
                        }
                    }
                }
                
                if (found)
                    break;
            }
                
            if (found == false)
                break;
        }
        
        // add adges
        for (int i = 0; i < boundary.size(); i++)
        {
            int start = boundary[i].x1 * 100 + boundary[i].y1;
            int end = boundary[i].x2 * 100 + boundary[i].y2;
            
            edges[start].insert(end);
            edges[end].insert(start);
            
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
                startx = x1;
                starty = min(y1, y2);
                
                nextx = x1;
                nexty = max(y1, y2);
            }
            else if (x1 == x2 && x1 == maxX)
            {
                startx = x1;
                starty = max(y1, y2);
                
                nextx = x1;
                nexty = min(y1, y2);
            }
            else if (y1 == y2 && y1 == minY)
            {
                startx = max(x1, x2);
                starty = y1;
                
                nextx = min(x1, x2);
                nexty = y1;
            }
            else if (y1 == y2 && y1 == maxY)
            {
                startx = min(x1, x2);
                starty = y1;
                
                nextx = max(x1, x2);
                nexty = y1;
            }
            
            // start find polygon in clockwise
            vector<int> vertices;
            
            int first = startx * 100 + starty, second = nextx * 100 + nexty;
            vertices.push_back(first);
            vertices.push_back(second);
            
            int times = 0;
            while (true)
            {
                //cout << "first: " << first / 100 << " " << first % 100 << endl;
                //cout << "second: " << second / 100 << " " << second % 100 << endl;
                
                int third = getNextVertices(first, second);
                vertices.push_back(third);
                
                //cout << "third: " << third / 100 << " " << third % 100 << endl;
                
                if (third == vertices.front())
                    break;
                
                times++;
                
                //if (times > 100)
                //{
                    //cout << "loop!" << endl;
                    //return 0;
                //}
                        
                first = second;
                second = third;
            }
            
            //cout << "process end." << endl;
            
            // remove the used boundary
            for (int i = 0; i < vertices.size() - 1; i++)
                for (int j = boundary.size() - 1; j >= 0; j--)
                {
                    int start = boundary[j].x1 * 100 + boundary[j].y1;
                    int next = boundary[j].x2 * 100 + boundary[j].y2;
                    
                    if ((vertices[i] == start && vertices[i + 1] == next) ||
                        (vertices[i] == next && vertices[i + 1] == start))
                            boundary.erase(boundary.begin() + j);
                }
            
            counter[vertices.size() - 1]++;
            lots++;
        }
        
        // output the result
        if (cases++)
            cout << endl;
        cout << "Case " << cases << endl;
        
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
