// Jack Straws
// UVa ID: 273
// Verdict: Accepted
// Submission Date: 2016-05-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>

using namespace std;

struct point
{
    int x, y;
};

struct segment
{
    point start, end;
};

bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x))
        && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

double direction(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

bool segmentsIntersect(segment a, segment b)
{
    double d1, d2, d3, d4;
    
    d1 = direction(a.start, a.end, b.start);
    d2 = direction(a.start, a.end, b.end);
    d3 = direction(b.start, b.end, a.start);
    d4 = direction(b.start, b.end, a.end);
    
    if ((d1 * d2 < 0) && (d3 * d4 < 0))
        return true;

    if (d1 == 0 && pointInBox(b.start, a.start, a.end))
        return true;

    if (d2 == 0 && pointInBox(b.end, a.start, a.end))
        return true;

    if (d3 == 0 && pointInBox(a.start, b.start, b.end))
        return true;

    if (d4 == 0 && pointInBox(a.end, b.start, b.end))
        return true;
        
    return false;
}

int main(int argc, char *argv[])
{
    bool first = true;
    
    int cases;
    cin >> cases;
    
    while (cases--)
    {
        int n, x1, y1, x2, y2;
        cin >> n;
        
        vector < segment > segments;
        for (int i = 1; i <= n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            segments.push_back((segment){(point){x1, y1}, (point){x2, y2}});
        }
        
        bool connected[13][13];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                connected[i][j] = false;
        
        // The straw which intersect itself is CONNECTED!
        for (int i = 0; i < segments.size(); i++)
            for (int j = 0; j < segments.size(); j++)
                if (segmentsIntersect(segments[i], segments[j]))
                    connected[i][j] = true;

                
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (connected[i][k] && connected[k][j])
                        connected[i][j] = true;
        if (first)
            first = false;
        else
            cout << endl;
            
        int a, b;
        while (cin >> a >> b, a && b)
            cout << (connected[a - 1][b - 1] ? "CONNECTED" : "NOT CONNECTED") << endl;
    }
    
	return 0;
}
