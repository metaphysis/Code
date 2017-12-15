// Colourful Flowers
// UVa ID: 11152
// Verdict: Accepted
// Submission Date: 2017-12-15
// UVa Run Time: 0.040s
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

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout << fixed << setprecision(4);

    double a, b, c;
    while (cin >> a >> b >> c)
    {
        double p = (a + b + c) / 2;
        double St = p * (p - a) * (p - b) * (p - c);
        double Sout = PI * pow(a * b * c, 2) / (16 * St);
        double Sin = PI * (4 * St) / pow(a + b + c, 2);
        St = sqrt(St);
        cout << (Sout - St) << ' ' << (St - Sin) << ' ' << Sin << '\n';
    }

    return 0;
}
