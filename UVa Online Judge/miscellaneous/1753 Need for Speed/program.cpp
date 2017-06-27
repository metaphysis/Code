// Need for Speed
// UVa ID: 1753
// Verdict: Accepted
// Submission Date: 2017-06-15
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    double t, d, s;

    while (cin >> n >> t)
    {
        double low = 10000.0, up = 2000000.0;

        vector<double> di, si;
        for (int i = 1; i <= n; i++)
        {
            cin >> d >> s;
            di.push_back(d), si.push_back(s);
            if (low > s) low = s;
        }
        
        low = -low;

        double middle, total = 0.0;
        int iterations = 0;

        while (fabs(total - t) > 1e-9 && iterations++ < 60)
        {
            total = 0.0;
            middle = (low + up) / 2.0;
            for (int i = 0; i < di.size(); i++) total += (di[i] / (si[i] + middle));
            if (total > t) low = middle;
            else up = middle;
        }

        cout << fixed << setprecision(9) << middle << '\n';
    }
    
    return 0;
}
