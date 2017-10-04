// Duathlon
// UVa ID: 10385
// Verdict: Accepted
// Submission Date: 2016-08-02
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

const double epsilon = 1e-6;

struct speed
{
    double v1, v2;
};

vector<speed> contestants;

double f(double t, double r)
{
    double min_value = r / contestants.front().v1 + (t - r) / contestants.front().v2;
    for (int i = 1, size = contestants.size(); i < size - 1; i++)
        min_value = min(min_value, r / contestants[i].v1 + (t - r) / contestants[i].v2);
    return r / contestants.back().v1 + (t - r) / contestants.back().v2 - min_value;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    double t;
    while (cin >> t)
    {
        int n;
        cin >> n;
        
        double v1, v2;
        contestants.clear();
        
        for (int j = 1; j <= n; j++)
        {
            cin >> v1 >> v2;
            contestants.push_back((speed){v1, v2});
        }
        
        double left = 0, right = t;
        while (fabs(right - left) > epsilon)
        {
            double leftThird = left + (right - left) / 3;
            double rightThird = right - (right - left) / 3;

            if (f(t, leftThird) > f(t, rightThird))
                left = leftThird;
            else
                right = rightThird;
        }

        if (f(t, left) > 0) cout << "The cheater cannot win.\n";
        else
        {
            cout << "The cheater can win by ";
            cout << fixed << setprecision(0) << -f(t, left) * 3600;
            cout << " seconds with r = ";
            cout << setprecision(2) << left << "km and k = ";
            cout << setprecision(2) << (t - left) << "km.\n";
        }
    }
    
	return 0;
}
