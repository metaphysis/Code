#include <bits/stdc++.h>

using namespace std;

const int MAXN = 102400, CHILDREN = 26, OFFSET = 'a';

struct Trie
{
    int cnt, root, child[MAXN][CHILDREN], ending[MAXN];

    Trie()
    {
        root = cnt = 1;
        ending[root] = 0;
        memset(child[root], 0, sizeof(child[root]));
    }

    void insert(const string s)
    {
        int *current = &root;
        for (auto c : s)
        {
            current = &child[*current][c - OFFSET];
            if (!(*current))
            {
                *current = ++cnt;
                memset(child[cnt], 0, sizeof(child[cnt]));
                ending[cnt] = 0;
            }
        }
        ending[*current] = 1;
    }

    bool query(const string s)
    {
        int *current = &root;
        for (auto c : s)
        {
            if (!(*current)) break;
            current = &child[*current][c - OFFSET];
        }
        return (*current && ending[*current]);
    }
};
