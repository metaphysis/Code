// Always on the run
// UVa ID: 590
// Verdict: Accepted
// Submission Date: 2016-09-26
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    vector<vector<int>> schedule[12];
    int cost[1100][12];
    
    int n, k, cases = 0;
    while (cin >> n >> k, n)
    {
        for (int i = 1; i <= n; i++)
            schedule[i].clear();
        int total = n * (n - 1), count;
        for (int i = 1; i <= n; i++)
        {
            schedule[i].push_back(vector<int>(1, 0));
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                {
                    schedule[i].push_back(vector<int>(1, 0));
                    continue;
                }
                
                cin >> count;
                vector<int> lines(count);
                for (int l = 0; l < count; l++)
                    cin >> lines[l];
                schedule[i].push_back(lines);
            }
        }
        
        memset(cost, 0, sizeof(cost));

        //for (int i = 1; i <= n; i++)
        //    for (int j = 1; j <= n; j++)
        //    {
        //        for (int l = 0; l < schedule[i][j].size(); l++)
        //            cout << schedule[i][j][l] << ' ';
        //        cout << '\n';
        //    }
        
        for (int i = 1; i <= n; i++)
            cost[1][i] = schedule[1][i][0];

        // dp
        for (int i = 2; i <= k; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                for (int l = 1; l <= n; l++)
                {
                    if (l == j) continue;
                    int fee = schedule[j][l][(i - 1) % schedule[j][l].size()];
                    if (fee == 0 || cost[i - 1][j] == 0) continue;
                    
                    if (cost[i][l] == 0)
                        cost[i][l] = cost[i - 1][j] + fee;
                    else
                        cost[i][l] = min(cost[i][l], cost[i - 1][j] + fee);
                }
            }
            
            //for (int j = 1; j <= n; j++)
            //    cout << cost[i][j] << ' ';
            //cout << '\n';
        }
        
        cout << "Scenario #" << ++cases << '\n';
        if (cost[k][n] > 0)
            cout << "The best flight costs " << cost[k][n] << ".\n\n";
        else
            cout << "No flight possible.\n\n";
    }
    
	return 0;
}
