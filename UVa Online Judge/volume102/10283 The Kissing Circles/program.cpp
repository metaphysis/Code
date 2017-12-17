// The Kissing Circles
// UVa ID: 10283
// Verdict: Accepted
// Submission Date: 2017-12-17
// UVa Run Time: 0.060s
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
    cout << fixed << setprecision(10);

    double R, N;
    
    while (cin >> R >> N)
    {
        if (N == 1)
        {
            cout << R << ' ' << 0.0 << ' ' << 0.0 << '\n';
            continue;
        }
        
        if (N == 2)
        {
            cout << (R / 2) << 0.0 << ' ' << (0.5 * PI * R * R) << '\n';
            continue;
        }
        
        double A = (N - 2) * PI / N;
        double r = R * cos(A / 2) / (1 + cos(A / 2));
        double S = r * r * tan(A / 2) * N;
        double I = S - N * r * r * (A / 2);
        double E = PI * R * R - I - N * PI * r * r;
        
        cout << r << ' ' << I << ' ' << E << '\n';
    }

    return 0;
}
