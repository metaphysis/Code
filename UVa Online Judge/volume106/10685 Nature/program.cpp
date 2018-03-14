// Nature
// UVa ID: 10685
// Verdict: Accepted
// Submission Date: 2018-01-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 30010;

int parent[MAXV], ranks[MAXV], cnt[MAXV];

void makeSet(int N)
{
    for (int i = 0; i <= N; i++) parent[i] = i, ranks[i] = 1;
}

// 带路径压缩的查找，使用递归实现。
int findSet1(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet1(parent[x]));
}

// 带路径压缩的查找，使用迭代实现。
int findSet2(int x)
{
    int ancestor = x, temp;

    while (ancestor != parent[ancestor]) ancestor = parent[ancestor];
    while (x != ancestor) {
        temp = parent[x];
        parent[x] = ancestor;
        x = temp;
    }

    return x;
}

//  集合的按秩合并。
bool unionSet(int x, int y)
{
    x = findSet1(x), y = findSet1(y);
    
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x, ranks[x] += ranks[y];
        else parent[x] = y, ranks[y] += ranks[x];
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int C, R;
    while (cin >> C >> R)
    {
        if (C == 0 && R == 0) break;
        
        map<string, int> indexer;
        string name1, name2;

        for (int i = 1; i <= C; i++)
        {
            cin >> name1;
            indexer[name1] = i;
        }
        
        makeSet(C);
        
        for (int i = 1; i <= R; i++)
        {
            cin >> name1 >> name2;
            unionSet(indexer[name1], indexer[name2]);
        }
        
        cout << *max_element(ranks, ranks + C + 1) << '\n';
    }

    return 0;
}
