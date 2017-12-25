// Bingo!
// UVa ID: 12239
// Verdict: Accepted
// Submission Date: 2017-12-25
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

    int n, b, number[100];
    
    while (cin >> n >> b, n > 0)
    {
        for (int i = 0; i < b; i++) cin >> number[i];
        sort(number, number + b);
        if (number[0] != 0)
        {
            cout << "N\n";
            continue;
        }
        
        bool flag = false;
        for (int i = 1; i <= n; i++)
        {
            bool found = false;
            for (int j = 0; j < b; j++)
            {
                if (number[j] + i <= number[b - 1])
                {
                    if (binary_search(number, number + b, number[j] + i))
                    {
                        found = true;
                        break;
                    }
                }
            }
            if (!found)
            {
                flag = true;
                break;
            }
        }
        
        if (flag) cout << "N\n";
        else cout << "Y\n";
    }

    return 0;
}
