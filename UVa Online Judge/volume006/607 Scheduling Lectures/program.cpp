// Scheduling Lectures
// UVa ID: 607
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const int INF = 250000000;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, L, C, topics[1024], DI[1024][1024];
    int cases = 0;
    
    while (cin >> n, n > 0)
    {
        cin >> L >> C;
        
        int lectures = 0, minutes = 0;
        
        for (int i = 1; i <= n; i++)
        {
            cin >> topics[i];
            if (minutes + topics[i] >= L)
            {
                lectures++;
                if (minutes + topics[i] > L)
                    minutes = topics[i];
                else
                    minutes = 0;
            }
            else
                minutes += topics[i];
        }
        if (minutes > 0) lectures++;
        
        for (int i = 0; i <= lectures; i++)
            for (int j = 0; j <= n; j++)
                DI[i][j] = INF;
        
        for (int i = 1; i <= lectures; i++)
            for (int j = 1; j <= n; j++)
            {
            }
            
        int minDI = INF;
        for (int i = 1; i <= lectures; i++)
            minDI = min(minDI, DI[n][i]);

        if (cases++ > 0) cout << '\n';
        cout << "Case " << cases << ":\n";
        cout << "Minimum number of lectures: " << lectures << '\n';
        cout << "Total dissatisfaction index: " << minDI << '\n';
    }
    
    return 0;
}
