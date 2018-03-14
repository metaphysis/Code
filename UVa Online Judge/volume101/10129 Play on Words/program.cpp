// Play on Words
// UVa ID: 10129
// Verdict: Accepted
// Submission Date: 2017-08-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 26;
int parent[MAXV], ranks[MAXV];

void makeSet()
{
    for (int i = 0; i < MAXV; i++) parent[i] = i, ranks[i] = 0;
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

        for (int i = 1; i <= n; i++)
        {
            cin >> word;
            int u = word.front() - 'a', v = word.back() - 'a';
            if (findSet(u) != findSet(v)) unionSet(u, v);
            letterUsed[u] = letterUsed[v] = 1;
            outDegree[u]++, inDegree[v]++;
        }

        bool eulerianTrail = true;
        int moreOne = 0, lessOne = 0;
        for (int first = -1, i = 0; i < 26; i++)
        {
            if (!letterUsed[i]) continue;

            if (first == -1) first = i;
            if (findSet(first) != findSet(i)) { eulerianTrail = 0; break; }

            int diff = inDegree[i] - outDegree[i];
            if (abs(diff) >= 2) { eulerianTrail = 0; break; }
            if (diff == 1 && ++moreOne > 1) { eulerianTrail = 0; break; }
            if (diff == -1 && ++lessOne > 1) { eulerianTrail = 0; break; }
        }

        if (moreOne != lessOne) eulerianTrail = false;

        if (eulerianTrail) cout << "Ordering is possible.\n";
        else cout << "The door cannot be opened.\n";
    }

    return 0;
}
