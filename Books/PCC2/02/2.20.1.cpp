#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

struct NODE {
    int lc, rc, key, d;
} lt[MAXN];

int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (lt[x].key > lt[y].key) swap(x, y);
    lt[x].rc = merge(lt[x].rc, y);
    if (lt[lt[x].rc].d > lt[lt[x].lc].d) swap(lt[x].lc, lt[x].rc);
    lt[x].d = lt[lt[x].rc].d + 1;
    return x;
}

int top(int x) { return lt[x].key; }

void pop(int x) { return merge(lt[x].lc, lt[x].rc); }

int root = 0;
void push(int x, int y) {
    ++root;
    lt[root].key = y;
    lt[root].lc = lt[root].rc = lt[root].d = 1;
    return merge(x, root);
}

int main(int argc, char *argv[])
{
    return 0;
}
