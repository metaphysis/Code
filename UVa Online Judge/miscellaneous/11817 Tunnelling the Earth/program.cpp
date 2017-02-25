// Tunnelling the Earth
// UVa ID: 11817
// Verdict: Accepted
// Submission Date: 2017-02-24
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

const double epsilon = 1e-8;

double great_circle_distance(double R, double plat, double plong, double qlat, double qlong)
{
    return R * acos(sin(plat) * sin(qlat) + cos(plat) * cos(qlat) * cos(plong - qlong));
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    double latitude1, longitude1, latitude2, longitude2;
    double pi = 2 * acos(0), R = 6371009.0;
    
    cin >> n;
    for (int c = 1; c <= n; c++)
    {
        cin >> latitude1 >> longitude1 >> latitude2 >> longitude2;
        latitude1 *= pi / 180.0, longitude1 *= pi / 180.0;
        latitude2 *= pi / 180.0, longitude2 *= pi / 180.0;
        
        double dist_circle = great_circle_distance(R, latitude1, longitude1, latitude2, longitude2);
        double dist_line = 2.0 * R * sin(dist_circle / R / 2.0);
        
        double diff = fabs(dist_circle - dist_line);
        cout << fixed << setprecision(0) << diff << '\n';
    }
    
    return 0;
}
