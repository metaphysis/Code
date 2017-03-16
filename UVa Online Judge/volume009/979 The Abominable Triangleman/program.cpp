// The Abominable Triangleman
// UVa ID: 979
// Verdict: Accepted
// Submission Date: 2017-03-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
        if (x != b.x) return x < b.x;
        else return y < b.y;
    }
};

struct triangle
{
    point v1, v2, v3;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, n, x, y;
    int rotate[4][2][2] = {{{1, 0}, {0, 1}}, {{0, -1}, {1, 0}}, {{-1, 0}, {0, -1}}, {{0, 1}, {-1, 0}}};
    int mirror[2][2][2] = {{{1, 0}, {0, 1}}, {{-1, 0}, {0, 1}}};
    point v1, v2, v3;
    vector<point> points;
    
    while (cin >> v1.x >> v1.y)
    {
        cin >> v2.x >> v2.y;
        cin >> v3.x >> v3.y;
        cin >> n;
        
        points.clear();
        for (int i = 1; i <= n; i++)
        {
            cin >> x >> y;
            points.push_back(point{x, y});
        }
        
        sort(points.begin(), points.end());
        
        v2.x -= v1.x, v2.y -= v1.y;
        v3.x -= v1.x, v3.y -= v1.y;
        
        vector<triangle> triangles;
        point vv2, vv3, vvv2, vvv3;
        
        for (int i = 0; i < 2; i++)
        {
            vv2.x = mirror[i][0][0] * v2.x + mirror[i][0][1] * v2.y;
            vv2.y = mirror[i][1][0] * v2.x + mirror[i][1][1] * v2.y;
            
            vv3.x = mirror[i][0][0] * v3.x + mirror[i][0][1] * v3.y;
            vv3.y = mirror[i][1][0] * v3.x + mirror[i][1][1] * v3.y;
            
            for (int j = 0; j < 4; j++)
            {
                vvv2.x = rotate[j][0][0] * vv2.x + rotate[j][0][1] * vv2.y;
                vvv2.y = rotate[j][1][0] * vv2.x + rotate[j][1][1] * vv2.y;
                
                vvv3.x = rotate[j][0][0] * vv3.x + rotate[j][0][1] * vv3.y;
                vvv3.y = rotate[j][1][0] * vv3.x + rotate[j][1][1] * vv3.y;
                
                // v1 of triangle is not used.
                triangles.push_back(triangle{v1, vvv2, vvv3});
            }
        }
        
        vector<point> answer;
        point t1, t2;
        
        for (int i = 0; i < points.size(); i++)
        {
            for (int j = 0; j < triangles.size(); j++)
            {
                t1.x = points[i].x + triangles[j].v2.x;
                t1.y = points[i].y + triangles[j].v2.y;
                if (!binary_search(points.begin(), points.end(), t1)) continue;
                
                t2.x = points[i].x + triangles[j].v3.x;
                t2.y = points[i].y + triangles[j].v3.y;
                if (!binary_search(points.begin(), points.end(), t2)) continue;
                
                answer.push_back(points[i]);
                answer.push_back(t1);
                answer.push_back(t2);
                goto print;
            }
        }
        
        print:
        if (cases++ > 0) cout << '\n';
        sort(answer.begin(), answer.end());
        for (int i = 0; i < answer.size(); i++)
            cout << answer[i].x << ' ' << answer[i].y << '\n';
    }
    
    return 0;
}
