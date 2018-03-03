// R U Kidding Mr. Feynman?
// UVa ID: 10509
// Verdict: Accepted
// Submission Date: 2018-03-03
// UVa Run Time: 0.030s
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

    double n;
    while (cin >> n, n > 0)
    {
        double r = (int)(pow(n, 1.0 / 3.0) + 1e-7);
        r += (n - pow(r, 3)) / pow(r, 2) / 3.0;
        cout << fixed << setprecision(4) << r << '\n';
    }

    return 0;
}
