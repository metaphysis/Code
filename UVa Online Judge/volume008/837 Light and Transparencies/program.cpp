// Light and Transparencies
// UVa ID: 837
// Verdict: Accepted
// Submission Date: 2016-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
    double x, y;
    
    bool operator<(const point &b) const
    {
        if (x + EPSILON < b.x) return true;
        else return false;
    }
};

struct segment
{
    point start, end;
    double transparency;
    
    bool operator<(const segment &b) const
    {
        if (start.x + EPSILON < b.start.x) return true;
        else return false;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, NL;
    double x1, y1, x2, y2, transparency;
    
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        vector<point> points;
        vector<segment> segments;

        cin >> NL;
        
        for (int j = 1; j <= NL; j++)
        {
            cin >> x1 >> y1 >> x2 >> y2 >> transparency;
            
            if (x2 + EPSILON < x1) swap(x1, x2), swap(y1, y2);
            points.push_back((point){x1, y1});
            points.push_back((point){x2, y2});
            segments.push_back((segment){(point){x1, y1}, (point){x2, y2}, transparency});
        }
        
        sort(points.begin(), points.end());
        sort(segments.begin(), segments.end());
        
        vector<segment> output;
        for (int i = 0; i < points.size() - 1; i++)
        {
            transparency = 1.0;
            for (int j = 0; j < segments.size(); j++)
            {
                if (points[i].x + EPSILON >= segments[j].start.x &&
                    points[i].x + EPSILON <= segments[j].end.x)
                    transparency *= segments[j].transparency;
            }
            output.push_back((segment){points[i], points[i + 1], transparency});
        }
        
        cout.setf(ios::fixed);
        cout.precision(3);
        
        cout << output.size() + 2 << '\n';
        cout << "-inf " << output.front().start.x << " 1.000\n";
        for (int i = 0; i < output.size(); i++)
        {
            cout << output[i].start.x << ' ' << output[i].end.x << ' ';
            cout << output[i].transparency << '\n';
        }
        cout << output.back().end.x << " +inf 1.000\n";
    }
    
	return 0;
}
