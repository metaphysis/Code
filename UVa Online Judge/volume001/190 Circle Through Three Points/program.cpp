// Circle Through Three Points
// UVa IDs: 190
// Verdict: Accepted
// Submission Date: 2016-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// 当参数为 0 时忽略输出，但是题目描述中并未提到这一点。很容易让人 Wrong Answer。

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const double EPSILON = 10E-3;

int main(int argc, char *argv[])
{
    double ax, ay, bx, by, cx, cy;
    double h, k, r;
    double c, d, e;
    double temp;
    
    while (cin >> ax >> ay >> bx >> by >> cx >> cy)
    {
        h = (ax * ax - bx * bx + ay * ay - by * by) * (ay - cy);
        h -= (ax * ax - cx * cx + ay * ay - cy * cy) * (ay - by);
        h /= (2 * (ay - cy) * (ax - bx) - 2 * (ay - by) * (ax - cx));

        k = (ax * ax - bx * bx + ay * ay - by * by) * (ax - cx);
        k -= (ax * ax - cx * cx + ay * ay - cy * cy) * (ax - bx);
        k /= (2 * (ay - by) * (ax - cx) - 2 * (ay - cy) * (ax - bx));
        
        r = sqrt(pow(ax - h, 2) + pow(ay - k, 2));
        
        if (fabs(h) < EPSILON)
        {
            cout << "x^2";
        }
        else
        {
            cout << "(x ";
            cout << (h < 0 ? "+" : "-");
            temp = h < 0 ? -h : h;
            cout << " " << fixed << setprecision(3) << temp << ")^2";
        }

        cout << " + ";
        
        if (fabs(k) < EPSILON)
        {
            cout << "y^2";
        }
        else
        {
            cout << "(y ";
            cout << (k < 0 ? "+" : "-");
            temp = k < 0 ? -k : k;
            cout << " " << fixed << setprecision(3) << temp << ")^2";
        }
        
        cout << " = ";
        cout << fixed << setprecision(3) << r << "^2";
        cout << "\n";
        
        cout << "x^2 + y^2 ";
        
        c = h < 0 ? -2 * h : 2 * h;
        if (fabs(c) > EPSILON)
        {
            cout << (h < 0 ? "+" : "-");
            cout << " " << fixed << setprecision(3) << c << "x ";
        }

        d = k < 0 ? -2 * k : 2 * k;
        if (fabs(d) > EPSILON)
        {
            cout << (k < 0 ? "+" : "-");
            cout << " " << fixed << setprecision(3) << d << "y ";
        }
        
        e = h * h + k * k - r * r;
        if (fabs(e) > EPSILON)
        {
            cout << (e < 0 ? "-" : "+");
            e = e < 0 ? -e : e;
            cout << " " << fixed << setprecision(3) << e << " ";
        }
        
        cout << "= 0";
        
        cout << "\n\n";
    }
    
	return 0;
}
