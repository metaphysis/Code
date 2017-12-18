// The Grazing Cow
// UVa ID: 10678
// Verdict: Accepted
// Submission Date: 2017-12-18
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

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    double D, L;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> D >> L;
        double a = L / 2, b = sqrt(pow(L / 2, 2) - pow(D / 2, 2));
        cout << fixed << setprecision(3) << (PI * a * b) << '\n';
    }

    return 0;
}
