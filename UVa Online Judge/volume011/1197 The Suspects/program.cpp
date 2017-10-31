// The Susptects
// UVa ID: 1197
// Verdict: Accepted
// Submission Date: 2017-11-01
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

const int MAXV = 30010;

int parent[MAXV], ranks[MAXV];

void makeSet(int n)
{
    for (int i = 0; i < n; i++) parent[i] = i, ranks[i] = 0;
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

    int n, m, k, z1, z2;
    while (cin >> n >> m, n > 0)
    {
        makeSet(n);
        for (int i = 1; i <= m; i++)
        {
            cin >> k >> z1;
            for (int j = 2; j <= k; j++)
            {
                cin >> z2;
                unionSet(z1, z2);
            }
        }
        
        int cnt = 0;
        for (int i = 0; i < n; i++)
            if (findSet(i) == findSet(0))
                cnt++;

        cout << cnt << '\n';
    }
    
    return 0;
}
