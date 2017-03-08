// Many paths, one destination
// UVa ID: 988
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 2.930s
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

vector<vector<int>> edges;

int ways = 0;

void dfs(int i)
{
    if (edges[i].size() == 0)
    {
        ways++;
        return;
    }
    
    for (int j = 0; j < edges[i].size(); j++)
        dfs(edges[i][j]);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, m, choice, cases = 0;
    while (cin >> n)
    {
        edges.clear();
        edges.assign(n, vector<int>());
        
        for (int i = 0; i < n; i++)
        {
            cin >> m;
            for (int j = 0; j < m; j++)
            {
                cin >> choice;
                edges[i].push_back(choice);
            }
        }

        ways = 0;
        dfs(0);
        
        if (cases++ > 0) cout << '\n';
        cout << ways << '\n';
    }
    
    return 0;
}
