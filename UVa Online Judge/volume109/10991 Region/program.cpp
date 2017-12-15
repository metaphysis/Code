// Region
// UVa ID: 10991
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

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int k = 1; k <= cases; k++)
    {
        double R1, R2, R3;
        
        cin >> R1 >> R2 >> R3;
        
        double a = R1 + R2, b = R2 + R3, c = R3 + R1;
        double p = (a + b + c) / 2.0;
        double St = sqrt(p * (p - a) * (p - b) * (p - c));
        
        double A = acos((b * b + c * c - a * a) / (2.0 * b * c));
        double B = acos((a * a + c * c - b * b) / (2.0 * a * c));
        double C = acos((a * a + b * b - c * c) / (2.0 * a * b));
        
        double Sa = R3 * R3 * A / 2;
        double Sb = R1 * R1 * B / 2;
        double Sc = R2 * R2 * C / 2;
        
        double Sg = St - Sa - Sb - Sc;

        cout << fixed << setprecision(6) << Sg << '\n'; 
    }

    return 0;
}
