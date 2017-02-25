// Travelling Distance
// UVa ID: 10897
// Verdict: Accepted
// Submission Date: 2017-02-25
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
#include <vector>

using namespace std;

double great_circle_distance(double R, double plat, double plong, double qlat, double qlong)
{
    return R * acos(sin(plat) * sin(qlat) + cos(plat) * cos(qlat) * cos(plong - qlong));
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    double latitude1, longitude1, latitude2, longitude2;
    double a1, b1, c1, d1, e1, f1, a2, b2, c2, d2, e2, f2;
    char X1, Y1, X2, Y2;
    double pi = 2 * acos(0), R = 6371.01;
    
    cin >> n;
    for (int c = 1; c <= n; c++)
    {
        cin >> a1 >> b1 >> c1 >> X1 >> d1 >> e1 >> f1 >> Y1;
        cin >> a2 >> b2 >> c2 >> X2 >> d2 >> e2 >> f2 >> Y2;
        
        latitude1 = (a1 + b1 / 60.0 + c1 / 3600.0) * pi / 180.0;
        longitude1 = (d1 + e1 / 60.0 + f1 / 3600.0) * pi / 180.0;
        latitude2 = (a2 + b2 / 60.0 + c2 / 3600.0) * pi / 180.0;
        longitude2 = (d2 + e2 / 60.0 + f2 / 3600.0) * pi / 180.0;
        
        if (X1 == 'S') latitude1 = -latitude1;
        if (Y1 == 'W') longitude1 = -longitude1;
        if (X2 == 'S') latitude2 = -latitude2;
        if (Y2 == 'W') longitude2 = -longitude2;
        
        double dist_circle = great_circle_distance(R, latitude1, longitude1, latitude2, longitude2);
        cout << fixed << setprecision(2) << dist_circle << '\n';
    }
    
    return 0;
}
