// Network
// UVa ID: 315
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.190s
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

vector<set<int>> edges, connected;
vector<bool> visited;

void dfs(int start)
{
    for (auto next : connected[start])
        if (visited[next] == false)
        {
            visited[next] = true;
            dfs(next);
        }
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        int n = stoi(line);
        if (n == 0) break;
        
        edges.clear();
        edges.resize(n + 1, set<int>());
            
        while (getline(cin, line), line != "0")
        {
            istringstream iss(line);
            int start, next;
            iss >> start;
            while (iss >> next)
                edges[start].insert(next), edges[next].insert(start);
        }
   
        if (n == 1)
        {
            cout << "0" << endl;
            continue;
        }
        
        visited.resize(n + 1);
            
        int counter = 0;
        for (int i = 1; i <= n; i++)
        {
            connected.clear();
            for (auto s : edges)
                connected.push_back(s);
                    
            for (int x = 1; x <= n; x++)
                connected[x].erase(i);
            connected[i].clear();
                
            fill(visited.begin(), visited.end(), false);
            int start = (i - 1 > 0 ? i - 1 : i + 1);
            visited[start] = true;
            dfs(start);
            
            for (int x = 1; x <= n; x++)
                if (visited[x] == false && x != i)
                {
                    counter++;
                    break;
                }
        }
        
        cout << counter << '\n';
    }
    
	return 0;
}
