// Beverages
// UVa ID: 11060
// Verdict: Accepted
// Submission Date: 2018-02-04
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

int main(int argc, char *argv[])
{
    string beer1, beer2;
    map<string, int> indexer;
    map<int, string> names;
    vector<int> edges[110];
    int n, m, cases = 0, indegree[110], visited[110];

    while (cin >> n) {
        for (int u = 1; u <= n; u++)
        {
            edges[u].clear();
            indegree[u] = 0;
            visited[u] = 0;
        }
        
        for (int i = 1; i <= n; i++)
        {
            cin >> beer1;
            indexer[beer1] = i;
            names[i] = beer1;
        }

        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> beer1 >> beer2;
            edges[indexer[beer1]].push_back(indexer[beer2]);
            indegree[indexer[beer2]]++;
        }

        cout << "Case #" << ++cases;
        cout << ": Dilbert should drink beverages in this order:";

        int printed = 0;
        while (printed < n)
        {
            int u = 1;
            while (u <= n && (indegree[u] || visited[u])) u++;
            cout << ' ' << names[u];
            visited[u] = 1;
            for (auto v : edges[u]) indegree[v]--;
            printed++;
        }
        cout << ".\n\n";

        indexer.clear();
        names.clear();
    }

    return 0;
}
