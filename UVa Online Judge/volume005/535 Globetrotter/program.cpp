// Globetrotter
// UVa ID: 535
// Verdict: Accepted
// Submission Date: 2016-08-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

double great_circle_distance(double R, double plat, double plong, double qlat, double qlong)
{
    return R * acos(sin(plat) * sin(qlat) + cos(plat) * cos(qlat) * cos(plong - qlong));
}

double haversine_formula(double R, double plat, double plong, double qlat, double qlong)
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
            double D = haversine_formula(R, location[from].first, location[from].second, location[to].first, location[to].second);
            cout << fixed << setprecision(0) << D << " km\n";
        }
    }
    
	return 0;
}
