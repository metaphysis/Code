// More Triangles ... THE AMBIGUOUS CASE
// UVa ID: 376
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct triangle
{
    int index;
    double a, b, B, side1, side2;
};

const double PI = 2.0 * acos(0.0);
const double EPSILON = 1e-7;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int cases = 0;
    double a, b, B;
    vector<triangle> triangles;
    
    while (cin >> a >> b >> B)
    {
        if (a == 0.0 && b == 0.0 && B == 0.0) break;
        
        if (fabs(B) <= EPSILON)
        {
            triangles.push_back((triangle){++cases, a, b, B, a + b, fabs(a - b)});
            continue;
        }
        
        if (a == 0.0 || b == 0.0 || B >= 180.0)
        {
            triangles.push_back((triangle){++cases, a, b, B, -1.0, -1.0});
            continue;
        }
        
        double angle = B;
        B = B * PI / 180.0;
        if (angle < 90.0 - EPSILON)
        {
            if (b < a * sin(B) - EPSILON)
                triangles.push_back((triangle){++cases, a, b, angle, -1.0, -1.0});
            else if (fabs(b - a * sin(B)) <= EPSILON)
                triangles.push_back((triangle){++cases, a, b, angle, a * sin(B), -1.0});
            else
            {
                if (b >= a)
                {
                    double A = asin(sin(B) * a / b);
                    double C = PI - A - B;
                    double c = sqrt(a * a + b * b - 2.0 * a * b * cos(C));
                    triangles.push_back((triangle){++cases, a, b, angle, c, -1.0});
                }
                else
                {
                    triangle aTriangle;
                    double offset = sqrt(b * b - a * a * sin(B) * sin(B));
                    aTriangle = (triangle){++cases, a, b, angle, a * cos(B) + offset, a * cos(B) - offset};
                    triangles.push_back(aTriangle);
                }
            }
        }
        else if (angle > 90.0 + EPSILON)
        {
            if (b < a - EPSILON)
                triangles.push_back((triangle){++cases, a, b, angle, -1.0, -1.0});
            else
            {           
                double A = asin(sin(B) * a / b);
                double C = PI - A - B;
                double c = sqrt(a * a + b * b - 2.0 * a * b * cos(C));
                triangles.push_back((triangle){++cases, a, b, angle, c, -1.0});
            }
        }
        else
        {
            if (b <= a + EPSILON)
                triangles.push_back((triangle){++cases, a, b, angle, -1.0, -1.0});
            else
                triangles.push_back((triangle){++cases, a, b, angle, sqrt(b * b - a * a), -1.0});
        }
    }

    cout << "Case    A      B    THETA  # of    Side   Side" << endl;
    cout << " #     side   side  (deg)  Triags    1      2" << endl;
    for (int i = 0; i < triangles.size(); i++)
    {
        cout << setw(4) << right << triangles[i].index;
        cout << setw(7) << right << fixed << setprecision(2) << triangles[i].a;
        cout << setw(7) << right << fixed << setprecision(2) << triangles[i].b;
        cout << setw(7) << right << fixed << setprecision(2) << triangles[i].B;
        cout << setw(6) << right << ((int)(triangles[i].side1 > 0.0) + (int)(triangles[i].side2 > 0.0));
        if (triangles[i].side1 > 0.0)
            cout << setw(9) << right << fixed << setprecision(2) << triangles[i].side1;
        if (triangles[i].side2 > 0.0)
            cout << setw(7) << right << fixed << setprecision(2) << triangles[i].side2;
        cout << endl;
    }
    cout << endl;
    cout << "END OF REPORT for " << cases << " cases" << endl;
    
	return 0;
}
