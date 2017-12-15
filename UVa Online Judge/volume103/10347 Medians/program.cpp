// Medians
// UVa ID: 10347
// Verdict: Accepted
// Submission Date: 2017-12-15
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

const double EPSILON = 1e-7;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double A, B, C, a, b, c;

    while (cin >> A >> B >> C)
    {
        if (A < EPSILON || B < EPSILON || C < EPSILON) { cout << "-1.000\n"; continue; }

        a = A * 2 / 3, b = B / 3, c = C * 2 / 3;

        double root = a * a - 2 * b * b + c * c;
        if (root < 0) { cout << "-1.000\n"; continue; }
        double x1 = sqrt(root / 2);
        double x2 = (a * a - c * c) / (4 * x1);
        root = b * b - x2 * x2;
        if (root <= EPSILON) { cout << "-1.000\n"; continue; }
        double y2 = sqrt(root);
        
        double pcx = 3 * x2, pcy = 3 * y2;
        double mbx = (x1 + pcx) / 2, mby = pcy / 2;
        double aa = sqrt(pow(mbx + x1, 2) + pow(mby, 2));
        if (fabs(aa - A) > EPSILON) { cout << "-1.000\n"; continue; }

        double max =(-x1 + pcx) / 2, may = pcy / 2;
        double cc = sqrt(pow(max - x1, 2) + pow(may, 2));
        if (fabs(cc - C) > EPSILON) { cout << "-1.000\n"; continue; }
        
        double La = sqrt(pow(pcx + x1, 2) + pow(pcy, 2));
        double Lb = sqrt(pow(pcx - x1, 2) + pow(pcy, 2));
        double Lc = 2 * x1;
        double p = (La + Lb + Lc) / 2;
        double area = sqrt(p * (p - La) * (p - Lb) * (p - Lc));
        cout << fixed << setprecision(3) << area << '\n';
    }

    return 0;
}
