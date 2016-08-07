// Sunrise
// UVa ID: 415
// Verdict: Accepted
// Submission Date: 2016-08-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

const double pi = 2 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    double Sr = 432000, Er = 3950, D = 92900000;
    
    double L = sqrt(D * D + Sr * Sr - Er * Er);
    double alpha = atan(Sr / D) + atan(L / Er);
    
    double seconds;
    while (cin >> seconds)
    {
        double h, beta = alpha - 2.0 * pi * seconds / 3600.0 / 24.0;

        h = (Er - D * cos(beta)) / sin(beta);
        
        if (h >= Sr)
        {
            cout << "0.000000\n";
            continue;
        }
        
        if (h <= -Sr)
        {
            cout << "1.000000\n";
            continue;
        }
        
        double percentage = acos(fabs(h) / Sr) / pi - fabs(h) * sqrt(Sr * Sr - h * h) / (pi * Sr * Sr);
        if (h < 0)
            percentage = 1.0 - percentage;
        cout << fixed << setprecision(6) << percentage << '\n';
    }
    
	return 0;
}
