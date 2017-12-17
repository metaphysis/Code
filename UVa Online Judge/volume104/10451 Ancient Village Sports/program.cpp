// Ancient Village Sports
// UVa ID: 10451
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

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    double n, A;
    
    while (cin >> n >> A, n >= 3)
    {
        cout << "Case " << ++cases << ": ";
        double a = (n - 2) * PI / n;
        double r = sqrt(A / (n * cos(a / 2) * sin(a / 2)));
        double spectators = PI * r * r - A;
        double officials = A - PI * r * r * sin(a / 2) * sin(a / 2);
        cout << fixed << setprecision(5) << spectators << ' ' << officials << '\n';
    }

    return 0;
}
