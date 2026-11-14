// persistent leftist tree

int root = 0;
int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (lt[x].key > lt[y].key) swap(x, y);
    int p = ++root;
    lt[p] = lt[x];
    lt[p].rc = merge(lt[x].rc, y);
    if (lt[lt[p].rc].ds > lt[lt[p].lc].ds) swap(lt[p].lc, lt[p].rc);
    lt[p].ds = lt[lt[p].rc].ds + 1;
    return p;
}
