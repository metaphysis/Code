// Floating-Point Numbers
// UVa ID: 11809
// Verdict: Accepted
// Submission Date: 2018-01-14
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

void search(double mantissa, int exponent)
{
    double mf = 0, df = 1.0;
    for (int m = 0; m <= 9; m++)
    {
        df /= 2; mf += df;
        for (int e = 1; e <= 30; e++)
        {
            double et = log10(2) * ((1 << e) - 1.0);
            int ei = (int)et;
            double ef = et - ei, mt = mf * pow(10.0, ef);
            if (mt > 1.0) mt /= 10.0, ei += 1;
            if (fabs(mt - mantissa) <= 1e-5 && ei == exponent)
            {
                cout << m << ' ' << e << '\n';
                return;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "0e0")
    {
        int ei = line.find('e');
        double mantissa = stold(line.substr(0, ei));
        int exponent = stoi(line.substr(ei + 1));
        if (mantissa > 1.0) mantissa /= 10.0, exponent += 1;
        search(mantissa, exponent);
    }

    return 0;
}
