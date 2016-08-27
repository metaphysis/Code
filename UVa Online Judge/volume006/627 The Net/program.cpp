// The Net
// UVa ID: 627
// Verdict: Accepted
// Submission Date: 2016-08-28
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

    int n, m, start, end;
    while (cin >> n)
    {
        cin.ignore(1024, '\n');
        
        map<int, set<int>> edges;
        
        string line, block;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            
            int hypen = line.find('-');
            start = stoi(line.substr(0, hypen));
            
            string routers = line.substr(hypen + 1);
            istringstream iss(routers);
            while (getline(iss, block, ','))
                edges[start].insert(stoi(block));
        }
        
        cout << "-----\n";
        cin >> m;
        
        for (int j = 1; j <= m; j++)
        {
            cin >> start >> end;

            map<int, int> parent;
            set<int> visited;
            
            queue<int> unvisited;
            unvisited.push(start);
            parent[start] = -1;
            visited.insert(start);
            
            while (!unvisited.empty())
            {
                int current = unvisited.front();
                unvisited.pop();
                
                if (current == end)
                    break;
                    
                for (auto edge : edges[current])
                    if (visited.find(edge) == visited.end())
                    {
                        parent[edge] = current;
                        visited.insert(edge);
                        unvisited.push(edge);
                    }
            }
            
            if (parent.find(end) == parent.end())
                cout << "connection impossible\n";
            else
            {
                vector<int> path;
                while (parent[end] != -1)
                {
                    path.insert(path.begin(), end);
                    end = parent[end];
                }
                path.insert(path.begin(), end);
                for (int k = 0; k < path.size(); k++)
                {
                    if (k > 0)
                        cout << ' ';
                    cout << path[k];
                }
                cout << '\n';
            }
        }
    }
    
	return 0;
}
