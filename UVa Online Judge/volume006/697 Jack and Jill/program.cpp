// Jack and Jill
// UVa ID: 697
// Verdict: Accepted
// Submission Date: 2018-02-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

    cout.setf(ios::fixed);
    cout.precision(2);

    double UP, D, L, B, P, DOWN, V;
    int cases = 0;

    while (cin >> UP >> D >> L >> B >> P >> DOWN >> V)
    {
        if (cases++ > 0) cout << '\n';
        cout << "Scenario " << cases << ":\n";
        cout << "     up hill" << setw(19) << right << UP << " sec\n";
        cout << "     well diameter" << setw(13) << right << D << " in\n";
        cout << "     water level" << setw(15) << right << L << " in\n";
        cout << "     bucket volume" << setw(13) << right << B << " cu ft\n";
        cout << "     bucket ascent rate" << setw(8) << right << P << " in/sec\n";
        cout << "     down hill" << setw(17) << right << DOWN << " sec\n";
        cout << "     required volume" << setw(11) << right << V << " cu ft\n";

        double feetToInches = 12.0;
        double volume = 0, T = 0, dropDownOfWell = pow(feetToInches, 3.0) * 4.0 * B / (PI * D * D);
        V *= feetToInches, B *= feetToInches;
        while (volume + 1e-6 < V)
        {
            // UP to top of hill.
            T += UP;
            // Drop bucket to bottom of well.
            T += sqrt(L / 193.2);
            // Pull bucket up to top of well.
            T += L / P;
            // Every bucket changes height of well.
            L += dropDownOfWell;
            // Down to bottom of hill.
            T += DOWN;
            // Water volume carried.
            volume += B;
        }
        cout << "     TIME REQUIRED" << setw(13) << right <<  T << " sec\n";
    }

    return 0;
}
