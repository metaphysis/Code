// Tax Calculator
// UVa ID: 12342
// Verdict: Accepted
// Submission Date: 2017-12-30
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

    int cases, k, tax;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";

        cin >> k;
        
        tax = 0;
        if (k <= 180000)
        {
            cout << tax << '\n';
            continue;
        }
        
        k -= 180000;
        if (k <= 300000)
        {
            tax += k / 10;
            if (k % 10 != 0) tax++;
            if (tax < 2000) tax = 2000;
            cout << tax << '\n';
            continue;
        }
        else tax += 30000;
        
        k -= 300000;
        if (k <= 400000)
        {
            tax += k * 3 / 20;
            if ((k * 3) % 20 != 0) tax++;
            cout << tax << '\n';
            continue;
        }
        else tax += 60000;
        
        k -= 400000;
        if (k <= 300000)
        {
            tax += k / 5;
            if (k % 5 != 0) tax++;
            cout << tax << '\n';
            continue;
        }
        else tax += 60000;
        
        k -= 300000;
        tax += k / 4;
        if (k % 4 != 0) tax++;
        cout << tax << '\n';
    }
    return 0;
}
