// Horizon Line
// UVa ID: 972
// Verdict: Accepted
// Submission Date: 2017-03-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double epsilon = 1e-7;

struct segment
{
    double x1, x2, y;
    
    bool operator<(const segment& b) const
    {
        if (fabs(x1 - b.x1) > epsilon) return x1 > b.x1;
        else
        {
            if (fabs(y - b.y) > epsilon) return y < b.y;
            else return x2 > b.x2;
        }
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int fx, gx;
    double height, length;
    
    while (cin >> fx)
    {
        priority_queue<segment> segments;
        
        double start = 0.0;
        for (int i = 1; i <= fx; i++)
        {
            cin >> height >> length;
            segments.push(segment{start, start + length, height});
            start += length;
        }
        
        start = 0.0;
        cin >> gx;
        for (int i = 1; i <= gx; i++)
        {
            cin >> height >> length;
            segments.push(segment{start, start + length, height});
            start += length;
        }
        
        double minValue = 10.0;
        while (!segments.empty())
        {
            segment s1 = segments.top();
            segments.pop();
            
            if (!segments.empty())
            {
                segment s2 = segments.top();
                segments.pop();
                
                //cout << "S1: " << s1.x1 << ' ' << s1.x2 << ' ' << s1.y << '\n';
                //cout << "S2: " << s2.x1 << ' ' << s2.x2 << ' ' << s2.y << '\n';
                
                if (s1.x2 < s2.x1 + epsilon)
                {
                    minValue = min(minValue, s1.y);
                    segments.push(s2);
                }
                else if (s1.x1 + epsilon < s2.x1 && s1.x2 > s2.x1 + epsilon && s1.x2 + epsilon < s2.x2)
                {
                    minValue = min(minValue, s1.y);
                    if (s1.y > s2.y)
                    {
                        segments.push(segment{s2.x1, s1.x2, s1.y});
                        segments.push(segment{s1.x2, s2.x2, s2.y});
                    }
                    else segments.push(s2);
                }
                else if (fabs(s1.x1 - s2.x1) < epsilon)
                {
                    if (s1.x2 > s2.x2 || fabs(s1.x2 - s2.x2) < epsilon)  
                        segments.push(s1);
                    else
                    {
                        if (fabs(s1.y - s2.y) < epsilon)
                            segments.push(s2);
                        else
                        {
                            segments.push(s1);
                            segments.push(segment{s1.x2, s2.x2, s2.y});
                        }
                    }
                }
                else
                {
                    if (fabs(s1.x2 - s2.x2) < epsilon)
                    {
                        minValue = min(minValue, s1.y);
                        if (s1.y > s2.y || fabs(s1.y - s2.y) < epsilon)
                            segments.push(segment{s2.x1, s1.x2, s1.y});
                        else
                            segments.push(s2);
                    }
                    else
                    {
                        minValue = min(minValue, s1.y);
                        if (s1.y > s2.y || fabs(s1.y - s2.y) < epsilon)
                            segments.push(segment{s2.x1, s1.x2, s1.y});
                        else
                        {
                            segments.push(s2);
                            segments.push(segment{s2.x2, s1.x2, s1.y});
                        }
                    }
                }
            }
            else
            {
                minValue = min(minValue, s1.y);
            }
        }
        
        cout << fixed << setprecision(3) << minValue << '\n';
    }
    
    return 0;
}
