// Ecological Premium
// UVa ID: 10300
// Verdict: Accepted
// Submission Date: 2017-10-05
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

    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        int farmers;
        long long result = 0;
        
        cin >> farmers;
        for (int f = 1; f <= farmers; f++)
        {
            long long yard, animals, friendiness;
            cin >> yard >> animals >> friendiness;
            result += yard * friendiness;
        }
        cout << result << '\n';
    }
    
    return 0;
}
