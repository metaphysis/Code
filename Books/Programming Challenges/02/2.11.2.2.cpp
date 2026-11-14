#include <bits/stdc++.h>

using namespace std;

const int MAXN = 512, INF = 0x7f7f7f7f;

struct rectangle
{
    int x1, y1, x2, y2;
    rectangle(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0):
    x1(x1), y1(y1), x2(x2), y2(y2) {}
    bool isBad() { return x1 > x2 || y1 > y2; }
    bool isCell() { return x1 == x2 && y1 == y2; }
    bool contains(int r, int c) { return x1 <= r && r <= x2 && y1 <= c && c <= y2; }
    bool contains(rectangle q) { return x1 <= q.x1 && q.x2 <= x2 && y1 <= q.y1 && q.y2 <= y2; }
    bool intersects(rectangle q) { return !(x1 > q.x2 || y1 > q.y2 || x2 < q.x1 || y2 < q.y1); }
    rectangle getLU() { return rectangle(x1, y1, (x1 + x2) >> 1, (y1 + y2) >> 1); }
    rectangle getRU() { return rectangle(x1, ((y1 + y2) >> 1) + 1, (x1 + x2) >> 1, y2); }
    rectangle getLB() { return rectangle(((x1 + x2) >> 1) + 1, y1, x2, (y1 + y2) >> 1); }
    rectangle getRB() { return rectangle(((x1 + x2) >> 1) + 1, ((y1 + y2) >> 1) + 1, x2, y2); }
};

struct node
{
    int high;
    node* children[4];
};

int data[MAXN][MAXN];

node* getNode()
{
    node *nd = new node;
    nd->high = -INF;
    for (int i = 0; i < 4; i++) nd->children[i] = NULL;
    return nd;
}

void pushUp(node *nd)
{
    int high = -INF;
    for (int i = 0; i < 4; i++) {
        if (nd->children[i] == NULL) continue;
        high = max(high, nd->children[i]->high);
    }
    nd->high = high;
}

node* build(rectangle r)
{
    if (r.isBad()) return NULL;
    if (r.isCell()) {
        node *nd = getNode();
        nd->high = data[r.x1][r.y1];
        return nd;
    }

    node *nd = getNode();
    nd->children[0] = build(r.getLU());
    nd->children[1] = build(r.getRU());
    nd->children[2] = build(r.getLB());
    nd->children[3] = build(r.getRB());
    pushUp(nd);

    return nd;
}

int query(node *nd, rectangle r, rectangle qr)
{
    if (r.isBad()) return -INF;
    if (r.intersects(qr)) return -INF;
    if (qr.contains(r)) return nd->high;

    int q1 = query(nd->children[0], r.getLU(), qr);
    int q2 = query(nd->children[1], r.getRU(), qr);
    int q3 = query(nd->children[2], r.getLB(), qr);
    int q4 = query(nd->children[3], r.getRB(), qr);
    return max(max(q1, q2), max(q3, q4));
}

void update(node *nd, rectangle r, int ux, int uy, int v)
{
    if (r.isBad()) return;
    if (!r.contains(ux, uy)) return;
    if (r.isCell()) { nd->high = v; return; }

    update(nd->children[0], r.getLU(), ux, uy, v);
    update(nd->children[1], r.getRU(), ux, uy, v);
    update(nd->children[2], r.getLB(), ux, uy, v);
    update(nd->children[3], r.getRB(), ux, uy, v);
    pushUp(nd);
}

int main(int argc, char *argv[])
{
    return 0;
}
