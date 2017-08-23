// Euler Circuit
// UVa ID: 10735
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

int V, E;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        cin >> V >> E;
        
        int a, b;
        char d;
        
        vector<int> edges[V + 1];
        
        for (int i = 1; i <= E; i++)
        {
            cin >> a >> b >> d;
            if (d == 'U')
            {
                edges[a].push_back(b);
                edges[b].push_back(a);
            }
            else
            {
                edges[a].push_back(b);
            }
        }
        
        bool eulerian = true;

        int *id = new int[V + 1], *od = new int[V + 1];

        memset(id, 0, sizeof(int) * (V + 1));
        memset(od, 0, sizeof(int) * (V + 1));

        for (int u = 1; u <= V; u++)
            for (auto v : edges[u])
                od[u]++, id[v]++;

        int moreOne = 0, lessOne = 0, evenStart = -1, oddStart = -1;
        for (int u = 1; u <= V; u++)
        {
            int diff = od[u] - id[u];
            if (abs(diff) >= 2) { eulerian = false; break; }
            if (diff == 1 && ++moreOne > 1) { eulerian = false; break; }
            if (diff == -1 && ++lessOne > 1) { eulerian = false; break; }
            if (moreOne && oddStart < 0) oddStart = u;
            if (diff == 0 && evenStart < 0) evenStart = u;
        }

        delete [] id, od;

        if (moreOne != lessOne) { eulerian = false; }
        int start = oddStart >= 0 ? oddStart : evenStart;
        
        if (!eulerian) { cout << "No euler circuit exist\n"; continue; }
        
        stack<int> path;
        vector<int> circuit;
        
        path.push(1);
        int current = 1;
        
        while (!path.empty())
        {
            if (edges[current].size())
            {
                path.push(current);
                int next = edges[current].front();
                edges[current].erase(edges[current].begin());
                current = next;
            }
            else
            {
                circuit.push_back(current);
                current = path.top();
                path.pop();
            }
        }
        
        for (int i = circuit.size(); i >= 0; i--)
        {
            cout << circuit[i];
            if (i) cout << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
