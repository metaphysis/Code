// The Settlers of Catan
// UVa ID: 593
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

    int connected[30][30], indegree[30], n, m, from, to;
    
    while (cin >> n >> m, n)
    {
        memset(connected, 0, sizeof(connected));
        memset(indegree, 0, sizeof(indegree));

        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to;
            connected[from][to] = connected[to][from] = 1;
            indegree[from]++;
            indegree[to]++;
        }
        
        int total_in_degree = 0, odd_degree = 0;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] % 2 == 1)
                odd_degree++;
            total_in_degree += indegree[i];
        }
        
        while (odd_degree > 2)
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (connected[i][j] && (indegree[i] % 2) == 1 && (indegree[j] % 2) == 1)
                    {
                        connected[i][j] = connected[j][i] = 0;
                        indegree[i]--;
                        indegree[j]--;
                        odd_degree -= 2;
                        goto next;
                    }
            
            next:
            total_in_degree -= 2;
        }
        
        cout << total_in_degree / 2 << '\n';
    }
    
	return 0;
}
