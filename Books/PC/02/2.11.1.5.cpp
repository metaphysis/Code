const int MAXN = 512;

#define LCHILD(x) ((x >> 1) | 1)
#define RCHILD(x) ((x + 1) >> 1)

int n, m, data[MAXN][MAXN];

struct node { int field; } st[4 * MAXN][4 * MAXN];

node combine(node a, node b) { return node{max(a.field, b.field)}; }

void buildY(int px, int lx, int rx, int py, int ly, int ry)
{
    if (ly == ry) {
        if (lx == rx) st[px][py] = data[lx][ly];
        else st[px][py] = combine(st[LCHILD(px)][py], st[RCHILD(px)][py]);
    } else {
        int my = (ly + ry) >> 1;
        buildY(px, lx, rx, LCHILD(px), ly, my);
        buildY(px, lx, rx, RCHILD(py), my + 1, ry);
    }
}

void buildX(int px, int lx, int rx)
{
    if (lx != rx) {
        int mx = (lx + rx) >> 1;
        buildX(LCHILD(px), lx, mx);
        buildX(RCHILD(px), mx + 1, rx);
    }
    buildY(px, lx, rx, 0, 0, m - 1);
}
