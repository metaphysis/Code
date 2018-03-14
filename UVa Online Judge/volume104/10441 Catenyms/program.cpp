// Catenyms
// UVa ID: 10441
// Verdict: Accepted
// Submission Date: 2017-08-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

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

multiset<string> edges[26];

void dfs(int u, vector<string> &path)
{
    if (edges[u].size() > 0)
    {
        string word = *edges[u].begin();
        path.push_back(word);
        edges[u].erase(edges[u].begin());
        dfs(word.back() - 'a', path);
    }
    else
    {
        for (int i = path.size() - 1; i >= 0; i--)
        {
            vector<string> cycle;
            dfs(path[i].back() - 'a', cycle);
            path.insert(path.begin() + i + 1, cycle.begin(), cycle.end());
        }
    }
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

        int appeared[26] = {0}, id[26] = {0}, od[26] = {0};

        makeSet();

        for (int i = 0; i < 26; i++)
            edges[i].clear();

        for (int i = 1; i <= n; i++)
        {
            cin >> word;
            int u = word.front() - 'a', v = word.back() - 'a';
            if (findSet(u) != findSet(v)) unionSet(u, v);
            appeared[u] = appeared[v] = 1;
            od[u]++, id[v]++;
            edges[u].insert(word);
        }

        bool eulerian = true;
        int moreOne = 0, lessOne = 0, evenStart = -1, oddStart = -1;
        for (int first = -1, i = 0; i < 26; i++)
        {
            if (!appeared[i]) continue;

            if (first == -1) first = i;
            if (findSet(first) != findSet(i)) { eulerian = 0; break; }

            int diff = od[i] - id[i];
            if (abs(diff) >= 2) { eulerian = 0; break; }
            if (diff == 1 && ++moreOne > 1) { eulerian = 0; break; }
            if (diff == -1 && ++lessOne > 1) { eulerian = 0; break; }
            if (moreOne  && oddStart < 0) oddStart = i;
            if (diff == 0 && evenStart < 0) evenStart = i;
        }

        if (moreOne != lessOne) eulerian = false;
        if (!eulerian) { cout << "***\n"; continue; }

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
