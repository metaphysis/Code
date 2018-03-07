// Humidex
// UVa ID: 11241
// Verdict: Accepted
// Submission Date: 2018-03-06
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cout.setf(ios::fixed);
    cout.precision(1);

    char letter;
    double T, D, H;
    bool settedT, settedD, settedH;

    while (cin >> letter)
    {
        if (letter == 'E') break;

        settedT = settedD = settedH = false;

        if (letter == 'T') { cin >> T; settedT = true; }
        else if (letter == 'D') { cin >> D; settedD = true; }
        else if (letter == 'H') { cin >> H; settedH = true; }

        cin >> letter;
        if (letter == 'T') { cin >> T; settedT = true; }
        else if (letter == 'D') { cin >> D; settedD = true; }
        else if (letter == 'H') { cin >> H; settedH = true; }

        // humidex = temperature + h
        // h = (0.5555) * (e - 10.0)
        // e = 6.11 * exp(5417.7530 * ((1/273.16) - (1/(dewpoint + 273.16))))
        if (settedT && settedD)
        {
            double e = 6.11 * exp(5417.7530 * (1.0 / 273.16 - 1.0 / (D + 273.16)));
            double h = 0.5555 * (e - 10.0);
            H = T + h;
        } 
        else if (settedT && settedH)
        {
            double h = H - T;
            double e = h / 0.5555 + 10.0;
            D = 1.0 / (1.0 / 273.16 - log(e / 6.11) / 5417.7530) - 273.16;
        }
        else if (settedD && settedH)
        {
            double e = 6.11 * exp(5417.7530 * (1.0 / 273.16 - 1.0 / (D + 273.16)));
            double h = 0.5555 * (e - 10.0);
            T = H - h;
        }

        cout << "T " << T << " D " << D << " H " << H << '\n';
    }

    return 0;
}
