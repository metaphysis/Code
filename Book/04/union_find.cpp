#include <iostream>

using namespace std;

int parent[100000], ranks[100000];

void makeSet()
{
    for (int i = 0; i < 100000; i++)
    {
        parent[i] = i;
        ranks[i] = 0;
    }
}

// 带路径压缩的查找，使用递归实现。
int findSet1(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet1(parent[x]);
}

// 带路径压缩的查找，使用迭代实现。
int findSet2(int x)
{
    int ancestor = x, temp;
    while (ancestor != parent[ancestor])
        ancestor = parent[ancestor];
    while (x != ancestor)
    {
        temp = parent[x];
        parent[x] = ancestor;
        x = temp;
    }
    return x;
}

//  集合的按秩合并。
void unionSet(int x, int y)
{
    x = findSet(x);
    y = findSet(y);
    
    if (x == y)
        return;
        
    if (ranks[x] > ranks[y])
        parent[y] = x;
    else
    {
        parent[x] = y;
        if (ranks[x] == ranks[y])
            ranks[y]++;
    }
}

int main(int argc, char *argv[])
{
    makeSet();
    return 0;
}
