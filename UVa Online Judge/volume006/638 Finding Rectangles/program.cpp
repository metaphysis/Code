// Finding Rectangles
// UVa ID: 638
// Verdict: Accepted
// Submission Date: 2017-05-31
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct vertex
{
    char label;
    int x, y;
    
    bool operator<(const vertex &v) const
    {
        if (y != v.y) return y > v.y;
        else return x < v.x;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, points;    
    vertex vertices[32];
    
    while (cin >> points, points > 0)
    {
        for (int i = 0; i < points; i++)
            cin >> vertices[i].label >> vertices[i].x >> vertices[i].y;

        sort(vertices, vertices + points);
        
        vector<string> rectangles;
        for (int i = 0; i < points; i++)
            for (int j = i + 1; j < points; j++)
            {
                if (vertices[i].y != vertices[j].y) continue;

                for (int k = j + 1; k < points; k++)
                {
                    if (vertices[i].x != vertices[k].x) continue;
                    
                    for (int l = k + 1; l < points; l++)
                    {
                        if (vertices[k].y != vertices[l].y) continue;
                        if (vertices[j].x != vertices[l].x) continue;
                        
                        string rectangle;
                        rectangle += vertices[i].label;
                        rectangle += vertices[j].label;
                        rectangle += vertices[l].label;
                        rectangle += vertices[k].label;
                        rectangles.push_back(rectangle);
                    }
                }
            }
        
        cout << "Point set " << ++cases << ":";
        if (rectangles.size() == 0)
        {
            cout << " No rectangles\n";
            continue;
        }
        
        cout << '\n';
        sort(rectangles.begin(), rectangles.end());
        for (int i = 0; i < rectangles.size(); i++)
        {
            cout << ' ' << rectangles[i];
            if ((i + 1) % 10 == 0) cout << '\n';
        }
        if (rectangles.size() % 10 != 0) cout << '\n';
    }
    
    return 0;
}
