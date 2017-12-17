// Height to Area
// UVa ID: 10522
// Verdict: Accepted
// Submission Date: 2017-12-17
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const double EPSILON = 1e-10;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases;
    double Ha, Hb, Hc;

    cin >> n;
    while (n)
    {
        cin >> Ha >> Hb >> Hc;
        if (Ha <= EPSILON || Hb <= EPSILON || Hc <= EPSILON)
        {
            n--;
            cout << "These are invalid inputs!\n";
            continue;
        }

        double root =
            (1 / Ha + 1 / Hb + 1 / Hc) * (-1 / Ha + 1 / Hb + 1 / Hc) * (1 / Ha - 1 / Hb + 1 / Hc) * (1 / Ha +
            1 / Hb - 1 / Hc);
        if (root <= EPSILON)
        {
            n--;
            cout << "These are invalid inputs!\n";
            continue;
        }

        cout << fixed << setprecision(3) << (1.0 / sqrt(root)) << '\n';
    }

    return 0;
}
