// Is It A Tree?
// UVa ID: 615
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

    int from, to, cases = 0;
    while (cin >> from >> to)
    {
        if (from < 0)
            break;
        
        bool isTree = true;
        map<int, set<int>> edges;
        map<int, int> degrees;
        set<int> nodes;
        
        while (from > 0)
        {
            if (edges[from].find(to) != edges[from].end() || from == to)
                isTree = false;
            edges[from].insert(to);
            degrees[to]++;
            nodes.insert(from), nodes.insert(to);
            cin >> from >> to;
        }
        
        if (edges.size() == 0)
            isTree = true;
        else
        {
            int start;
            for (auto node : nodes)
                if (degrees.find(node) == degrees.end())
                {
                    start = node;
                    break;
                }

            set<int> visited;
            queue<int> unvisited;
            unvisited.push(start);
            while (!unvisited.empty())
            {
                int current = unvisited.front();
                if (visited.find(current) != visited.end())
                {
                    isTree = false;
                    break;
                }
                else
                    visited.insert(current);
                unvisited.pop();
                
                for (auto edge : edges[current])
                    unvisited.push(edge);
            }
            
            if (visited.size() != nodes.size())
                isTree = false;
        }
        
        if (isTree)
            cout << "Case " << ++cases << " is a tree.\n";
        else
            cout << "Case " << ++cases << " is not a tree.\n";
    }
    
	return 0;
}
