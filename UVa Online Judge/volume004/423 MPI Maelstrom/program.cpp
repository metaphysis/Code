// MPI Maelstrom
// UVa ID: 423
// Verdict: Accepted
// Submission Date: 2016-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

const long long MAX_TIMES = numeric_limits<int>::max();

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long n, times[110][110];
    
    while (cin >> n)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                times[i][j] = MAX_TIMES;
        
        string digits;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= i - 1; j++)
            {
                cin >> digits;
                if (digits == "x") continue;
                else
                {
                    times[i][j] = stoll(digits);
                    times[j][i] = times[i][j];
                }
            }
            
        for (int i = 1; i <= n; i++)
            times[i][i] = 0;
            
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (times[i][j] > times[i][k] + times[k][j])
                        times[i][j] = times[i][k] + times[k][j];
        
        // from THE first node to another NODE                
        long long max_delay = 0;
        for (int j = 1; j <= n; j++)
            max_delay = max(max_delay, times[1][j]);

        cout << max_delay << '\n';
    }
    
	return 0;
}
