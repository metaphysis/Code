// Test
// UVa ID: 10731
// Verdict: Accepted
// Submission Date: 2017-10-19
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

const int MAXV = 30;
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

    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        map<char, int> indexer;
        int cnt = 0;

        initialize();

        for (int i = 1; i <= n; i++)
        {
            char letter;
            vector<char> question;
            for (int j = 1; j <= 5; j++)
            {
                cin >> letter;
                question.push_back(letter);
                if (indexer.find(letter) == indexer.end())
                    indexer[letter] = ++cnt;
            }
            
            char answer;
            cin >> answer;
            if (indexer.find(answer) == indexer.end())
                indexer[answer] = ++cnt;
                
            for (auto c : question)
            {
                if (c == answer) continue;
                edges[indexer[answer]].push_back(indexer[c]);
            }
        }
        
        for (int u = 1; u <= cnt; u++)
            if (!dfn[u])
                tarjan(u);
                
        if (cases++ > 0) cout << '\n';
        vector<string> sets(cscc);
        
        for (auto p : indexer)
            sets[scc[p.second] - 1] += p.first;
        
        for (int i = 0; i < cscc; i++)
            sort(sets[i].begin(), sets[i].end());
        sort(sets.begin(), sets.end());
        for (int i = 0; i < cscc; i++)
        {
            for (int j = 0; j < sets[i].length(); j++)
            {
                if (j) cout << ' ';
                cout << sets[i][j];
            }
            cout << '\n';
        }
    }
    
    return 0;
}
