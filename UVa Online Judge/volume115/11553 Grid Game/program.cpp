// Grid Game
// UVa ID: 11553
// Verdict: Accepted
// Submission Date: 2017-11-11
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

int grid[10][10];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];

        vector<int> s(n);
        iota(s.begin(), s.end(), 0);

        int least = 0x3fffffff;
        do
        {
            int sum = 0;
            for (int i = 0; i < n; i++)
                sum += grid[i][s[i]];
            least = min(least, sum);
        } while (next_permutation(s.begin(), s.end()));
        
        cout << least << '\n';
    }
    
    return 0;
}
