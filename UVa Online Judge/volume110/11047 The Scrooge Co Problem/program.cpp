// The Scrooge Co Problem
// UVa ID: 11047
// Verdict: Accepted
// Submission Date: 2018-02-18
// UVa Run Time: 0.000s
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

const int MAXV = 110, INF = 0x3f3f3f3f;

int cases, n, q, dist[MAXV][MAXV], parent[MAXV][MAXV];
string location[MAXV], employee, location1, location2;
map<string, int> indexer;
map<int, string> names;

void printPath(int i, int j)
{
    if (i != j)
    {
        printPath(i, parent[i][j]);
        cout << ' ';
    }
    cout << names[j];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        indexer.clear();
        names.clear();
        for (int i = 1; i <= n; i++)
        {
            cin >> location[i];
            indexer[location[i]] = i;
            names[i] = location[i];
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> dist[i][j];
                parent[i][j] = i;
            }
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                {
                    if (dist[i][k] != -1 && dist[k][j] != -1)
                    {
                        if (dist[i][j] == -1 || (dist[i][j] > dist[i][k] + dist[k][j]))
                        {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            parent[i][j] = parent[k][j];
                        }
                    }
                }
        cin >> q;
        for (int i = 1; i <= q; i++)
        {
            cin >> employee >> location1 >> location2;
            int u = indexer[location1], v = indexer[location2];
            if (dist[u][v] == -1)
            {
                cout << "Sorry Mr " << employee << " you can not go from ";
                cout << location1 << " to " << location2 << '\n';
            }
            else
            {
                cout << "Mr " << employee << " to go from ";
                cout << location1 << " to " << location2 << ", you will receive ";
                cout << dist[u][v] << " euros\n";
                cout << "Path:";
                if (u != v)
                    printPath(u, v);
                else
                    cout << location1 << ' ' << location2;
                cout << '\n';
            }
        }
        
    }

    return 0;
}
