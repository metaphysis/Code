// The Circumference of the Circle
// UVa ID: 438
// Verdict: Accepted
// Submission Date: 2016-07-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 3.141592653589793; // 2.0 * acos(0.0);

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    cout.precision(2);
    
    double x1, y1, x2, y2, x3, y3;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)
    {
        double a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        double b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
        double c = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
        double p = (a + b + c) / 2;
        double circumference = 2 * PI * (a * b * c / sqrt(p * (p - a) * (p - b) * (p - c)) / 4);
        cout << fixed << circumference << endl;
    }
    
	return 0;
}
