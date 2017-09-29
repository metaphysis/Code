// Dream
// UVa ID: 11414
// Verdict: Accepted
// Submission Date: 2017-09-29
// UVa Run Time: 0.020s
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

    int degree[1010], n;
    
    int cases = 0;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;

        for (int i = 0; i < n; i++) cin >> degree[i];
        
        bool graphic = true;
        for (int i = 0; i < n; i++)
        {
            sort(degree, degree + n, greater<int>());

            if (degree[0] == 0) break;

            if (degree[0] < 0)
            {
                graphic = false;
                break;
            }
            
            if (degree[0] >= (n - i))
            {
                graphic = false;
                break;
            }
            
            for (int j = 1; j <= degree[0]; j++)
                if (--degree[j] < 0)
                {
                    graphic = false;
                    break;
                }
            if (!graphic) break;
            
            degree[0] = 0;
        }
        
        cout << (graphic ? "Yes\n" : "No\n");
    }
    
    return 0;
}
