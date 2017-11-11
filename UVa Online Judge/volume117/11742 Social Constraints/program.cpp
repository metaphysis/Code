// Social Constraints
// UVa ID: 11742
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

struct constraint
{
    int a, b, c;
} constraints[24];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m;
    
    while (cin >> n >> m, n > 0)
    {
        for (int i = 0; i < m; i++)
            cin >> constraints[i].a >> constraints[i].b >> constraints[i].c;
            
        vector<int> seat(n);
        iota(seat.begin(), seat.end(), 0);
        
        int valid = 0;
        do
        {
            bool conflicted = false;
            for (int i = 0; i < m; i++)
            {
                if (constraints[i].c > 0)
                {
                    if (abs(seat[constraints[i].a] - seat[constraints[i].b]) > constraints[i].c)
                    {
                        conflicted = true;
                        break;
                    }
                }
                else
                {
                    if (abs(seat[constraints[i].a] - seat[constraints[i].b]) < -constraints[i].c)
                    {
                        conflicted = true;
                        break;
                    }
                }
            }
            if (!conflicted) valid++;
        } while (next_permutation(seat.begin(), seat.end()));
        
        cout << valid << '\n';
    }
    
    return 0;
}
