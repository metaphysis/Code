// Catenyms
// UVa ID: 10441
// Verdict: Accepted
// Submission Date: 2017-08-13
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

int parent[26], ranks[26];

void makeSet()
{
    for (int i = 0; i < 26; i++) parent[i] = i, ranks[i] = 0;
}

// 带路径压缩的查找，使用递归实现。
int findSet(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
}

//  集合的按秩合并。
bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    
    if (x != y)
    {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else
        {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

vector<string> edges[26];

void fleury(int u)
{
    for (int i = 0; i < edges[u].size(); i++)
        if (edges[u][i] != "*")
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;

        string word;

        int letterUsed[26] = {0}, inDegree[26] = {0}, outDegree[26] = {0};

        makeSet();

        for (int i = 0; i < 26; i++)
            edges[i].clear();

        for (int i = 1; i <= n; i++)
        {
            cin >> word;
            int u = word.front() - 'a', v = word.back() - 'a';
            if (findSet(u) != findSet(v)) unionSet(u, v);
            letterUsed[u] = letterUsed[v] = 1;
            outDegree[u]++, inDegree[v]++;
            edges[u].push_back(word);
        }

        bool eulerianPath = true;
        int moreOne = 0, lessOne = 0, evenStart = -1, oddStart = -1;
        for (int first = -1, i = 0; i < 26; i++)
        {
            if (!letterUsed[i]) continue;

            if (first == -1) first = i;
            if (findSet(first) != findSet(i)) { eulerianPath = 0; break; }

            int diff = outDegree[i] - inDegree[i];
            if (abs(diff) >= 2) { eulerianPath = 0; break; }
            if (diff == 1 && ++moreOne > 1) { eulerianPath = 0; break; }
            if (diff == -1 && ++lessOne > 1) { eulerianPath = 0; break; }
            if (moreOne  && oddStart < 0) oddStart = i;
            if (diff == 0 && evenStart < 0) evenStart = i;
        }

        if (moreOne != lessOne) eulerianPath = false;
        if (!eulerianPath) { cout << "***\n"; continue; }

        for (int i = 0; i < 26; i++) sort(edges[i].begin(), edges[i].end());

        vector<string> path;
        dfs((oddStart >= 0 ? oddStart : evenStart), path);
        for (int i = 0; i < path.size(); i++)
        {
            if (i > 0) cout << '.';
            cout << path[i];
        }
        cout << '\n';
    }

    return 0;
}
