// The Huge One
// UVa ID: 11344
// Verdict: Accepted
// Submission Date: 2018-03-12
// UVa Run Time: 0.000s
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

    int cases, m, n;
    string number;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> number;
        cin >> m;
        
        cout << number << " - ";
        bool wonderful = true;
        for (int i = 1; i <= m; i++)
        {
            cin >> n;
            if (!wonderful) continue;
            if (n == 1) continue;
            if (n == 2 && (number.back() - '0') % 2 == 0) continue;
            int r = 0;
            for (auto letter : number)
            {
                r = r * 10 + letter - '0';
                r %= n;
            }
            if (r != 0) wonderful = false;
        }
        
        if (wonderful) cout << "Wonderful.\n";
        else cout << "Simple.\n";
    }

    return 0;
}
