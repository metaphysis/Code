// Stack of Cylinders
// UVa ID: 915
// Verdict: Accepted
// Submission Date: 2017-03-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double epsilon = 1e-7;

struct circle
{
    int idx;
    double x, y, radius;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, n;
    
    while (cin >> n)
    {
        vector<circle> circles;
        
        double radius, maxX = 0.0;
        for (int i = 1; i <= n; i++)
        {
            cin >> radius;
            
            while (true)
            {
                if (circles.empty())
                {
                    circles.push_back(circle{i, radius, radius, radius});
                    break;
                }
        
                circle last = circles.back();
                double offsetx = sqrt(pow(last.radius + radius, 2) - pow(last.radius - radius, 2));
                circle current = circle{i, last.x + offsetx, radius, radius};
                
                if (last.x + offsetx - radius + epsilon < 0.0)
                {
                    circles.erase(circles.end() - 1);
                }
                else
                {
                    bool allFitted = true;
                    for (int j = circles.size() - 2; j >= 0; j--)
                    {
                        circle c = circles[j];
                        double dist = sqrt(pow(c.x - current.x, 2) + pow(c.y - current.y, 2));
                        if (dist + epsilon < (c.radius + current.radius))
                        {
                            circles.erase(circles.end() - 1);
                            allFitted = false;
                            break;
                        }
                    }
                    
                    if (allFitted)
                    {
                        circles.push_back(current);
                        break;
                    }
                }
            }
            
            maxX = max(maxX, circles.back().x + radius);
        }
        
        
        for (int i = circles.size() - 1; i >= 0; i--)
        {
            if (circles[i].x + circles[i].radius + epsilon < maxX)
            {
                circles.erase(circles.begin() + i);
                continue;
            }
            
            break;
        }

        if (cases++ > 0) cout << '\n';

        circle last = circles.back();
        cout << fixed << setprecision(1) << maxX << '\n';
        cout << circles.size() << '\n';
        for (int i = 0; i < circles.size(); i++)
            cout << circles[i].idx << '\n';
    }
    
    return 0;
}
