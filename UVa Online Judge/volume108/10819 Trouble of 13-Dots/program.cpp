// Trouble of 13-Dots
// UVa ID: 10819
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

    int m, n, value[10300][2], prices[110], favour[110];
    
    while (cin >> m >> n)
    {
        for (int i = 1; i <= n; i++)
            cin >> prices[i] >> favour[i];

        int money = m + 200;
        for (int j = 0; j <= money; j++)
            value[j][0] = value[j][1] = 0;

        for (int i = 1; i <= n; i++)
            for (int j = money; j >= prices[i]; j--)
                if (value[j - prices[i]][0] + favour[i] > value[j][0])
                {
                    value[j][0] = value[j - prices[i]][0] + favour[i];
                    value[j][1] = value[j - prices[i]][1] + prices[i];
                }

        if (m < 1800)
            cout << value[m][0] << '\n';
        else
        {
            if (value[money][1] > 2000)
                cout << value[money][0] << '\n';
            else
                cout << value[m][0] << '\n';
        }
    }
    
    return 0;
}
