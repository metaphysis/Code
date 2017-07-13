#include <iostream>

using namespace std;

const int MAXV = 100000;

int parent[MAXV], ranks[MAXV], numberOfVertices;

void makeSet()
{
    for (int i = 0; i < numberOfVertices; i++) parent[i] = i, ranks[i] = 0;
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
    makeSet();
    return 0;
}
