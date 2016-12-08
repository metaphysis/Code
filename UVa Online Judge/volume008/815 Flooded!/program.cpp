// Flooded!
// UVa ID: 815
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

int elevations[1000];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cout.setf(ios::fixed);
    cout.precision(2);

    int m, n, volume, submerged, cases = 0;
    while (cin >> m >> n, m > 0)
    {
        cout << "Region " << ++cases << '\n';

        for (int i = 0; i < m * n; i++)
            cin >> elevations[i];
        cin >> volume;

        sort(elevations, elevations + m * n);

        //int offset = 0;
        //if (elevations[0] < 0) offset = abs(elevations[0]);
        //for (int i = 0; i < m * n; i++)
        //    elevations[i] += offset;

        int heigth = 0;
        for (int i = 0; i < m * n; i++)
        {
            heigth += elevations[i];
            submerged = ((i + 1) * elevations[i] - heigth) * 100;
            if (submerged >= volume)
            {
                double level = (double)elevations[i - 1] + (double)(volume - submerged) / (double)((i - 1) * 100);
                cout << "Water level is " << level << " meters.\n";
                double percent = (double)(i + 1) / (double)(m * n);
                cout << percent << " percent of the region is under water.\n";
                break;
            }
        }
    }

	return 0;
}
