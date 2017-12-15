// Is This the Easiest Problem?
// UVa ID: 11479
// Verdict: Accepted
// Submission Date: 2017-12-15
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

typedef long long ll;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    ll sides[3];
    for (int cs = 1; cs <= cases; cs++)
    {
        for (int i = 0; i < 3; i++) cin >> sides[i];
        sort(sides, sides + 3);
        
        cout << "Case " << cs << ": ";
        if (sides[0] <= 0)
        {
            cout << "Invalid";
        }
        else
        {
            ll a = sides[0], b = sides[1], c = sides[2];
            if ((a + b) <= c || (a + c) <= b || (b + c) <= a)
            {
                cout << "Invalid";
            }
            else
            {
                if (a == b && b == c)
                {
                    cout << "Equilateral";
                }
                else if (a == b || b == c)
                {
                    cout << "Isosceles";
                }
                else
                {
                    cout << "Scalene";
                }
            }
        }

        cout << '\n';
    }

    return 0;
}
