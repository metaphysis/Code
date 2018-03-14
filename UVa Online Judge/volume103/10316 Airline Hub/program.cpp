// Airline Hub
// UVa ID: 10316
// Verdict: Accepted
// Submission Date: 2017-02-25
// UVa Run Time: 0.130s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double epsilon = 1e-8;

double great_circle_distance(double plat, double plong, double qlat, double qlong)
{
    return acos(sin(plat) * sin(qlat) + cos(plat) * cos(qlat) * cos(plong - qlong));
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    double lati[1010], latitude[1010], longi[1010], longitude[1010];
    double pi = 2 * acos(0), R = 6378.0;
    
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> lati[i] >> longi[i];
            latitude[i] = lati[i] / 180.0 * pi;
            longitude[i] = longi[i] / 180.0 * pi;
        }
        
        int minimal_i = 0;
        double max_dist = 0.0, current_dist;
        for (int j = 1; j < n; j++)
        {
            current_dist = great_circle_distance(latitude[0], longitude[0], latitude[j], longitude[j]);
            if (current_dist > max_dist)
                max_dist = current_dist;
        }
        
        for (int i = 1; i < n; i++)
        {
            double current_max_dist = 0.0;
            for (int j = 0; j < n; j++)
            {
                if (i == j) continue;
                current_dist = great_circle_distance(latitude[i], longitude[i], latitude[j], longitude[j]);
                if (current_dist > current_max_dist)
                    current_max_dist = current_dist;
                if (current_max_dist > max_dist + epsilon)
                    break;
            }
            
            if (current_max_dist < max_dist || fabs(current_max_dist - max_dist) < epsilon)
            {
                max_dist = current_max_dist;
                minimal_i = i;
            }
        }
        
        cout << fixed << setprecision(2) << lati[minimal_i] << ' ';
        cout << fixed << setprecision(2) << longi[minimal_i] << '\n';
    }
    
    return 0;
}
