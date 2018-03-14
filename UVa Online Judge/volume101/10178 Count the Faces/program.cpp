// Count the Faces
// UVa ID: 10178
// Verdict: Accepted
// Submission Date: 2017-10-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 256;

int parent[MAXV], ranks[MAXV];

void makeSet()
{
    for (int i = 0; i < MAXV; i++) parent[i] = i, ranks[i] = 0;
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
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
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

    int N, E, merges;
    char n1, n2;

    while (cin >> N >> E)
    {
        makeSet();
        
        merges = 0;
        for (int i = 1; i <= E; i++)
        {
            cin >> n1 >> n2;
            merges += unionSet(n1, n2);
        }
        
        cout << (1 + (N - merges) + E - N) << '\n';
    }
    
    return 0;
}
