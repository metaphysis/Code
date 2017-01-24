#include <iostream>

using namespace std;

const int MAXV = 100000;

int parent[MAXV], ranks[MAXV], number_of_vertices;

void make_set()
{
    for (int i = 0; i < number_of_vertices; i++) parent[i] = i, ranks[i] = 0;
}

// 带路径压缩的查找，使用递归实现。
int find_set1(int x)
{
    return (x == parent[x] ? x : parent[x] = find_set1(parent[x]));
}

// 带路径压缩的查找，使用迭代实现。
int find_set2(int x)
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
bool union_set(int x, int y)
{
    x = find_set1(x), y = find_set1(y);
    
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
    make_set();
    return 0;
}
