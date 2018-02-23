// Alternative Arborescence
// UVa ID: 11307
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

const int MAXV = 10010;

list<int> edges[MAXV];
int n, sum, visited[MAXV];
char seperator;

void dfs(int u, int color)
{
    sum += color;
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v, 3 - color);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++) edges[i].clear();
        cin.ignore(1024, '\n');
        for (int i = 1, u, v; i <= n; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            iss >> u >> seperator;
            while (iss >> v)
            {
                edges[u].push_back(v);
                edges[v].push_back(u);
            }
        }
        
        memset(visited, 0, n * sizeof(int));
        sum = 0;
        dfs(0, 1);
        int sum1 = sum;
        
        memset(visited, 0, n * sizeof(int));
        sum = 0;
        dfs(0, 2);
        int sum2 = sum;

        cout << min(sum1, sum2) << '\n';
    }

    return 0;
}
