// Morning Walk
// UVa ID: 10596
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

const int MAXV = 200;
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

    int N, R;
    
    while (cin >> N >> R)
    {
        int id[MAXV] = {0}, used[MAXV] = {0};
        
        makeSet();
        
        int u, v;
        for (int i = 1; i <= R; i++)
        {
            cin >> u >> v;
            if (findSet(u) != findSet(v)) unionSet(u, v);
            used[u] = used[v] = 1;
            id[u]++, id[v]++;
        }
        
        int oddDegree = 0, eulerianPath = 1;
        for (int first = -1, i = 0; i < N; i++)
        {
            if (!used[i]) continue;
            if (first == -1) first = i;
            if (findSet(first) != findSet(i)) { eulerianPath = 0; break; }
            if (id[i] % 2 != 0) { eulerianPath = 0; break; }
        }
        if (R == 0) eulerianPath = 0;

        cout << (eulerianPath ? "Possible" : "Not Possible") << '\n';
    }
    
    return 0;
}
