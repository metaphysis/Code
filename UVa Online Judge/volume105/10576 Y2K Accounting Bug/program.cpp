// Y2K Accounting Bug
// UVa ID: 10576
// Verdict: Accepted
// Submission Date: 2017-11-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// http://www.algorithmist.com/index.php/UVa_10576
//

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

int s, d, profit, report[20];

void dfs(int month, int earning, int balance)
{
    if (month == 13)
    {
        if (earning < 0) profit = max(profit, balance);
        return;
    }
    
    if (month >= 6 && earning >= 0) return;
    
    for (int i = 0; i <= 1; i++)
    {
        if (i == 0) report[month] = s;
        else report[month] = -d;
        
        if (month >= 6)
            dfs(month + 1, earning - report[month - 5] + report[month], balance + report[month]);
        else
            dfs(month + 1, earning + report[month], balance + report[month]);
            
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    while (cin >> s >> d)
    {
        profit = -0x3fffffff;

        dfs(1, 0, 0);
        
        if (profit > 0)
            cout << profit << '\n';
        else
            cout << "Deficit\n";
    }
    
    return 0;
}
