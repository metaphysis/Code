#include <bits/stdc++.h>

using namespace std;

const int MAXN = 512, INF = 0x7f7f7f7f;

struct rectangle
{
    int r1, c1, r2, c2;
    rectangle(int r1 = 0, int c1 = 0, int r2 = 0, int c2 = 0):
    r1(r1), c1(c1), r2(r2), c2(c2) {}
    bool isBad() { return r1 > r2 || c1 > c2; }
    bool isCell() { return r1 == r2 && c1 == c2; }
    bool contains(int r, int c) { return r1 <= r && r <= r2 && c1 <= c && c <= c2; }
    bool contains(rectangle q) { return r1 <= q.r1 && q.r2 <= r2 && c1 <= q.c1 && q.c2 <= c2; }
    bool intersects(rectangle q) { return !(r1 > q.r2 || c1 > q.c2 || r2 < q.r1 || c2 < q.c1); }
    rectangle getLU() { return rectangle(r1, c1, (r1 + r2) >> 1, (c1 + c2) >> 1); }
    rectangle getRU() { return rectangle(r1, ((c1 + c2) >> 1) + 1, (r1 + r2) >> 1, c2); }
    rectangle getLB() { return rectangle(((r1 + r2) >> 1) + 1, c1, r2, (c1 + c2) >> 1); }
    rectangle getRB() { return rectangle(((r1 + r2) >> 1) + 1, ((c1 + c2) >> 1) + 1, r2, c2); }
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
        nd->high = data[r.r1][r.c1];
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

void update(node *nd, rectangle r, int ur, int uc, int v)
{
    if (r.isBad()) return;
    if (r.isCell() && r.contains(ur, uc)) nd->high = v;
    else {
        if (r.getLU().contains(ur, uc))
            update(nd->children[0], r.getLU(), ur, uc, v);
        else if (r.getRU().contains(ur, uc))
            update(nd->children[1], r.getRU(), ur, uc, v);
        else if (r.getLB().contains(ur, uc))
            update(nd->children[2], r.getLB(), ur, uc, v);
        else if (r.getRB().contains(ur, uc))
            update(nd->children[3], r.getRB(), ur, uc, v);
        pushUp(nd);
    }
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

int main(int argc, char *argv[])
{
    return 0;
}
