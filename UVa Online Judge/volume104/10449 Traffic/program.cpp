// Traffic
// UVa ID: 10449
// Verdict: Accepted
// Submission Date: 2017-10-24
// UVa Run Time: 0.000s
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

const int MAXV = 210, MAXE = 100010, MAXW = 0xfffff, INF = 0x3fffffff;

struct edge { int from, to, weight; } edges[MAXE];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, r, x, y, q, d;
    int busyness[MAXV], dist[MAXV], old[MAXV], cycled[MAXV];

    while (cin >> n)
    {
        cout << "Set #" << ++cases << '\n';

        for (int i = 1; i <= n; i++)
            cin >> busyness[i];
            
        cin >> r;
        for (int i = 1; i <= r; i++)
        {
            cin >> x >> y;
            int t = pow(busyness[y] - busyness[x], 3);
            edges[i] = edge{x, y, t};
        }

        for (int i = 0; i <= n; i++) dist[i] = INF;
 
        dist[1] = 0;
        for (int k = 1; k < n; k++)
        {
            bool updated = false;
            for (int i = 1; i <= r; i++)
                if (dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
                {
                    dist[edges[i].to] = dist[edges[i].from] + edges[i].weight;
                    updated = true;
                }
            if (!updated) break;
        }

        memcpy(old, dist, sizeof(dist));
        for (int i = 1; i <= r; i++)
            if (dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
                dist[edges[i].to] = dist[edges[i].from] + edges[i].weight;
        
        memset(cycled, 0, sizeof(cycled));
        for (int i = 1; i <= n; i++)
            if (dist[i] < old[i] || dist[i] > MAXW)
                cycled[i] = 1;

        cin >> q;
        for (int i = 1; i <= q; i++)
        {
            cin >> d;
            if (cycled[d] || dist[d] < 3) cout << "?\n";
            else cout << dist[d] << '\n';
        }
    }
    
	return 0;
}
