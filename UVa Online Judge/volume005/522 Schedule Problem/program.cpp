// Schedule Problem
// UVa ID: 522
// Verdict: Accepted
// Submission Date: 2017-04-28
// UVa Run Time: 0.170s
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

struct edge
{
    int u, v, weight;
};

edge edges[20480];
int nedges, days[10240], n, part1, part2, cases = 0;
int dist[10240];
string constrain;

void addEdge(int u, int v, int weight)
{
    edges[nedges].u = u, edges[nedges].v = v, edges[nedges].weight = weight;
    nedges++;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        cout << "Case " << ++cases << ":\n";
        
        for (int i = 1; i <= n; i++)
            cin >> days[i];

        nedges = 0;
        while (cin >> constrain, constrain != "#")
        {
            cin >> part1 >> part2;
            
            if (constrain == "FAS") addEdge(part2, part1, days[part2]);
            else if (constrain == "FAF") addEdge(part2, part1, days[part2] - days[part1]);
            else if (constrain == "SAF") addEdge(part2, part1, -days[part1]);
            else addEdge(part2, part1, 0);
        }

        // add a vertex represent the day all parts done.
        n += 1;
        for (int i = 1; i < n; i++)
            addEdge(0, i, -days[i]);
        
        dist[0] = 0;
        for (int i = 1; i < n; i++)
            dist[i] = (1 << 30);

        int iterations = 0, updated = 0;
        do
        {
            updated = 0;
            for (int i = 0; i < nedges; i++)
            {
                int weight = dist[edges[i].u] + edges[i].weight;
                if (dist[edges[i].v] > weight)
                    updated++, dist[edges[i].v] = weight;
            }
        }
        while (updated && iterations++ < n);
    
        if (updated)
            cout << "impossible\n\n";
        else
        {
            int minDays = dist[1];
            for (int i = 2; i < n; i++)
                minDays = min(minDays, dist[i]);
            for (int i = 1; i < n; i++)
                cout << i << ' ' << (dist[i] - minDays) << '\n';
            cout << '\n';
        }
    }

    return 0;
}
