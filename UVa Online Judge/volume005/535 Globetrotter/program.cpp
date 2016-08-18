// Globetrotter
// UVa ID: 535
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

double greatCircleDistance(double R, double plat, double plong, double qlat, double qlong)
{
    return R * acos(sin(plat) * sin(qlat) + cos(plat) * cos(qlat) * cos(plong - qlong));
}

double haversineFormula(double R, double plat, double plong, double qlat, double qlong)
{
    double dlon = qlong - plong;
    double dlat = qlat - plat;
    double a = pow((sin(dlat / 2)), 2) + cos(plat) * cos(qlat) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = R * c;
    return d;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    double pi = 2 * acos(0), R = 6378.0;
    string city, from, to;
    map<string, pair<double, double>> location;
    double latitude, longtitude;
    
    while (cin >> city, city != "#")
    {
        cin >> latitude >> longtitude;
        location[city] = make_pair(latitude * pi / 180.0, longtitude * pi / 180.0);
    }
    
    while (cin >> from >> to, from != "#")
    {
        cout << from << " - " << to << '\n';
        
        if (location.find(from) == location.end() || location.find(to) == location.end())
        {
            cout << "Unknown\n";
            continue;
        }
        else
        {
            //if (from == to)
            //{
            //    cout << "0 km\n";
            //    continue;
            //}
            //double D = greatCircleDistance(R, location[from].first, location[from].second, location[to].first, location[to].second);
            //cout << fixed << setprecision(0) << D << " km\n";
            
            double D = haversineFormula(R, location[from].first, location[from].second, location[to].first, location[to].second);
            cout << fixed << setprecision(0) << D << " km\n";
        }
    }
    
	return 0;
}
