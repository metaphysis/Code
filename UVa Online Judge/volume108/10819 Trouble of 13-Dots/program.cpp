// Trouble of 13-Dots
// UVa ID: 10819
// Verdict: Accepted
// Submission Date: 2017-11-20
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int m, n, value[10300], prices[110], favour[110];
    
    while (cin >> m >> n)
    {
        for (int i = 1; i <= n; i++)
            cin >> prices[i] >> favour[i];

        memset(value, 0, sizeof(value));
        for (int i = 1; i <= n; i++)
            for (int j = m; j >= prices[i]; j--)
                value[j] = max(value[j], value[j - prices[i]] + favour[i]);

        if (m <= 1800) cout << value[m] << '\n';
        else
        {
            int r = value[m];
            memset(value, -1, sizeof(value));
            value[0] = 0;
            m += 200;
            for (int i = 1; i <= n; i++)
                for (int j = m; j >= prices[i]; j--)
                    if (value[j - prices[i]] >= 0)
                        value[j] = max(value[j], value[j - prices[i]] + favour[i]);
            for (int i = 2001; i <= m; i++)
                r = max(r, value[i]);
            cout << r << '\n';
        }
    }
    
    return 0;
}
