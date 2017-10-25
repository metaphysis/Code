// Flying to Fredericton
// UVa ID: 11280
// Verdict: Accepted
// Submission Date: 2017-10-25
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

const int MAXV = 110, MAXE = 1010, INF = 0x3fffffff;

struct edge { int from, to, weight; } edges[MAXE];

int dist[MAXV][MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int N;
        map<string, int> indexer;
        string city;
        
        cin >> N;
        for (int i = 1; i <= N; i++)
        {
            cin >> city;
            indexer[city] = i;
        }
        
        int M;
        cin >> M;
        string city1, city2;
        int cost;

        for (int i = 1; i <= M; i++)
        {
            cin >> city1 >> city2 >> cost;
            edges[i] = edge{indexer[city1], indexer[city2], cost};
        }
        
        for (int i = 0; i <= N + 1; i++)
            for (int j = 0; j <= N; j++)
                dist[i][j] = INF;
        dist[0][1] = 0;

        for (int k = 1; k <= N + 1; k++)
            for (int i = 1; i <= M; i++)
                if (dist[k][edges[i].to] > dist[k - 1][edges[i].from] + edges[i].weight)
                    dist[k][edges[i].to] = dist[k - 1][edges[i].from] + edges[i].weight;
        
        if (c > 1) cout << '\n';
        cout << "Scenario #" << c << '\n';

        int Q, stopover;
        cin >> Q;
        for (int i = 1; i <= Q; i++)
        {
            cin >> stopover;
            if (stopover >= N) stopover = N;
            
            stopover++;           

            int minCost = INF;
            for (int j = 0; j <= stopover; j++)
                minCost = min(minCost, dist[j][N]);

            if (minCost != INF)
                cout << "Total cost of flight(s) is $" << minCost << '\n';
            else
                cout << "No satisfactory flights\n";
        }
    }

    return 0;
}
