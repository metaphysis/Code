// Play on Words
// UVa ID: 10129
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

struct edge {
    int u, v;
};

int n;
vector<edge> edges;

const int MAXV = 100010;

int parent[MAXV], ranks[MAXV], numberOfVertices;

void makeSet()
{
    for (int i = 0; i < numberOfVertices; i++) parent[i] = i, ranks[i] = 0;
}

// 带路径压缩的查找，使用递归实现。
int findSet(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet1(parent[x]));
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

    int cases;
    cin >> cases;

    numberOfVertices = 26;
    
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        edges.clear();
        
        string word;
        for (int i = 1; i <= n; i++)
        {
            cin >> word;
            edges.push_back(edge{word.front() - 'a', word.back() - 'a'});
        }
        
        makeSet();
        
        for (auto e : edges)
        {
            if (findSet(e.u) != findSet(e.v)) unionSet(e.u, e.v);
        }
    }
    
    return 0;
}
