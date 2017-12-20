// Sub-Prime
// UVa ID: 11679
// Verdict: Accepted
// Submission Date: 2017-12-20
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

    int money[30], B, N, D, C, V;
    
    while (cin >> B >> N, B > 0)
    {
        for (int i = 1; i <= B; i++)
            cin >> money[i];
            
        for (int i = 1; i <= N; i++)
        {
            cin >> D >> C >> V;
            money[D] -= V;
            money[C] += V;
        }
        
        bool boilout = false;
        for (int i = 1; i <= B; i++)
            if (money[i] < 0)
            {
                boilout = true;
                break;
            }
            
        cout << (boilout ? 'N' : 'S') << '\n';
    }

    return 0;
}
