// XYZZY
// UVa ID: 10557
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

const int MAXV = 110, MAXE = 10010, INF = 0;

struct edge { int from, to, weight; } edges[MAXE];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, m, r, x, y, energy;
    int dist[MAXV];

    while (cin >> n, n > 0)
    {
        m = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> energy >> r;
            for (int j = 1; j <= r; j++)
            {
                cin >> x;
                edges[m++] = edge{i, x, -energy};
            }
        }

        for (int i = 1; i <= n; i++) dist[i] = INF;
 
        dist[1] = -100;
        for (int k = 1; k < n; k++)
        {
            bool updated = false;
            for (int i = 0; i < m; i++)
                if (dist[edges[i].to] > dist[edges[i].from] - edges[i].weight)
                {
                    dist[edges[i].to] = dist[edges[i].from] - edges[i].weight;
                    updated = true;
                }
            if (!updated) break;
        }

        int old = dist[n];
        for (int i = 0; i < m; i++)
            if (dist[edges[i].to] > dist[edges[i].from] - edges[i].weight)
                dist[edges[i].to] = dist[edges[i].from] - edges[i].weight;

        if (old != INF && (old < 0 || dist[n] < old)) cout << "winnable\n";
        else cout << "hopeless\n";
    }
    
	return 0;
}
