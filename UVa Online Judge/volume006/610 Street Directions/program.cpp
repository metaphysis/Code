// Street Directions
// UVa ID: 610
// Verdict: Accepted
// Submission Date: 2016-08-31
// UVa Run Time: 0.750s
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

vector<vector<int>> way;
int visited[1001];

void dfs(int i)
{
    for (auto e : way[i])
        if (e > 0 && !visited[e])
        {
            visited[e] = 1;
            dfs(e);
        }
}

bool connected(int i, int j)
{
    memset(visited, 0, sizeof(visited));
    dfs(i);
    return visited[j];
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, m, from, to, cases = 0;
    while (cin >> n >> m, n)
    {
        cout << ++cases << "\n\n";
        
        way.assign(n + 1, vector<int>());
        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to;
            way[from].push_back(to);
            way[to].push_back(from);
        }
        
        set<int> broken;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < way[i].size(); j++)
            {
                int save = way[i][j];
                if (broken.find(i * 10000 + save) == broken.end() &&
                    broken.find(save * 10000 + i) == broken.end())
                {
                    way[i][j] = -1;
                    if (!connected(i, save))
                        way[i][j] = save;
                    else
                        broken.insert(i * 10000 + save);
                }
            }
        
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < way[i].size(); j++)
                if (way[i][j] > 0)
                    cout << i << ' ' << way[i][j] << '\n';
            
        cout << "#\n";
    }
    
	return 0;
}
