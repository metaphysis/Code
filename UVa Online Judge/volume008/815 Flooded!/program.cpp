// Flooded!
// UVa ID: 815
// Verdict: Accepted
// Submission Date: 2016-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// uDebug NOTES: It is probably true that the judge's input contains no test
// cases where the water level of the answer is equal to the elevation of any
// region.

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

int elevations[1000];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cout.setf(ios::fixed);
    cout.precision(2);

    int m, n, volume, cases = 0;
    while (cin >> m >> n, m > 0)
    {
        cout << "Region " << ++cases << '\n';

        for (int i = 0; i < m * n; i++)
            cin >> elevations[i];
        cin >> volume;

        if (volume == 0)
        {
            double level = (double)(elevations[0]);
            cout << "Water level is " << level << " meters.\n";
            cout << "0.00 percent of the region is under water.\n\n";
            continue;
        }

        sort(elevations, elevations + m * n);

        bool flag = false;
        int filled = 0, lastFilled = 0, heigth = elevations[0];
        
        for (int i = 1; i < m * n; i++)
        {
            lastFilled = filled;
            filled = (i * elevations[i] - heigth) * 100;
            if (filled >= volume)
            {
                double level = (double)elevations[i - 1] + (double)(volume - lastFilled) / (double)(i * 100);
                cout << "Water level is " << level << " meters.\n";
                double percent = (double)(i) / (double)(m * n) * 100.0;
                cout << percent << " percent of the region is under water.\n";
                flag = true;
                break;
            }
            heigth += elevations[i];
        }
        
        if (!flag)
        {
            double level = elevations[m * n - 1] + (double)(volume - filled) / (double)(m * n * 100);
            cout << "Water level is " << level << " meters.\n";
            cout << "100.00 percent of the region is under water.\n";
        }
        
        cout << '\n';
    }

	return 0;
}
