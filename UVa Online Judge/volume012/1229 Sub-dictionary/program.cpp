// Sub-dictionary
// UVa ID: 1229
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

const int MAXV = 3010;
int dfstime = 0, dfn[MAXV], low[MAXV], scc[MAXV], cscc = 0;
vector<list<int>> edges(MAXV);
stack<int> s;

void initialize()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    for (int u = 1; u < MAXV; u++) edges[u].clear();
    memset(dfn, 0, sizeof(dfn)); memset(scc, 0, sizeof(scc));
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }

    if (low[u] == dfn[u])
    {
        ++cscc;
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        map<string, int> indexer;
        int cnt = 0;

        cin.ignore(1024, '\n');
        string line, word, definition;

        initialize();

        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            iss >> word;
            if (indexer.find(word) == indexer.end()) indexer[word] = ++cnt;
            while (iss >> definition)
            {
                if (indexer.find(definition) == indexer.end()) indexer[definition] = ++cnt;
                edges[indexer[word]].push_back(indexer[definition]);
            }
        }
        
        for (int u = 1; u <= cnt; u++)
            if (!dfn[u])
                tarjan(u);
                
        int number[MAXV] = {0};
        for (int u = 1; u <= cnt; u++)
            number[scc[u]]++;

        vector<string> dict;
        for (auto p : indexer)
            if (number[scc[p.second]] > 1)
                dict.push_back(p.first);
                
        sort(dict.begin(), dict.end());
        cout << dict.size() << '\n';
        for (int i = 0; i < dict.size(); i++)
        {
            if (i) cout << ' ';
            cout << dict[i];
        }
        cout << '\n';   
    }
    
    return 0;
}
