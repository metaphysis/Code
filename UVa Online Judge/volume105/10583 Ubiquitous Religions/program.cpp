// Ubiquitous Religions
// UVa ID: 10583
// Verdict: Accepted
// Submission Date: 2018-01-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 50010;

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

    int n, m, xi, yi, cases = 0;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0) break;
        makeSet();
        for (int i = 1; i <= m; i++)
        {
            cin >> xi >> yi;
            if (unionSet(xi, yi)) n--;
        }
        cout << "Case " << ++cases << ": " << n << '\n';
    }

    return 0;
}
