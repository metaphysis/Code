// Moliu Number Generator
// UVa ID: 11567
// Verdict: Accepted
// Submission Date: 2018-01-25
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

    long long S;
    while (cin >> S)
    {
        int operations = 0;
        while (S > 0)
        {
            if (S == 1) { operations += 1; break; }
            if (S == 2) { operations += 2; break; }
            if (S == 3) { operations += 3; break; }
    
            if (S & 1)
            {
                if ((((S - 1) >> 1) & 1) == 0) S -= 1;
                else S += 1;

                operations += 1;            
            }
            else 
            {
                S >>= 1;
                operations += 1;
            }
        }
        cout << operations << '\n';
    }

    return 0;
}
