// Romeo & Juliet!
// UVa ID: 10210
// Verdict: Accepted
// Submission Date: 2017-12-17
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

const double PI = 2.0 * acos(0);

inline double f(double a, double b, double x, double C)
{
    return a * sin(x) + b * sin(C - x);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double x1, y1, x2, y2, A, B, C;
    
    while (cin >> x1 >> y1 >> x2 >> y2 >> A >> B)
    {
        A = A / 180.0 * PI, B = B / 180.0 * PI;
        C = PI - A - B;
        
        double AB = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        double a = AB / sin(A);
        double b = AB / sin(B);
        
        double left = 0, right = C;
        for (int i = 1; i <= 50; i++)
        {
            double leftThird = left + (right - left) / 3;
            double rightThird = right - (right - left) / 3;
            
            double v1 = f(a, b, leftThird, C);
            double v2 = f(a, b, rightThird, C);
            
            if (v1 < v2) left = leftThird;
            else right = rightThird;
        }
        
        double D = f(a, b, left, C);
        cout << fixed << setprecision(3) << D << '\n';
    }

    return 0;
}
