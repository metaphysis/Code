// Best Coalitions
// UVa ID: 11658
// Verdict: Accepted
// Submission Date: 2017-11-17
// UVa Run Time: 0.010s
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

    int n, x, stocks[110], sum[10010];
    string percent;
    
    while (cin >> n >> x, n > 0)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> percent;
            int temp = 0;
            for (int j = 0; j < percent.length(); j++)
                if (isdigit(percent[j]))
                    temp = temp * 10 + percent[j] - '0';
            stocks[i] = temp;
        }
        
        memset(sum, 0, sizeof(sum));
        sum[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            if (i == x) continue;
            for (int j = 10000; j >= 0; j--)
                if (sum[j])
                    sum[j + stocks[i]] = 1;
        }
        
        double shares = 0.0;
        for (int i = 0; i <= 10000; i++)
            if (sum[i] && i + stocks[x] > 5000)
            {
                double temp = 100.0 * stocks[x] / (i + stocks[x]);
                if (temp > shares) shares = temp;
            }
        
        cout << fixed << setprecision(2) << shares << '\n';   
    }
    
    return 0;
}
