#include <bits/stdc++.h>

using namespace std;

const int MAXN = 512, INF = 0x7f7f7f7f;

int data[MAXN][MAXN];
int st[4 * MAXN * MAXN];

void pushUp(int p)
{
    int high = -INF;
    for (int i = 1; i <= 4; i++) high = max(high, st[4 * p + i]);
    st[p] = high;
}

void build(int p, int x1, int y1, int x2, int y2)
{
    if (x1 > x2 || y1 > y2) {
        st[p] = -INF;
        return;
    }
    if (x1 == x2 && y1 == y2) {
        st[p] = data[x1][y1];
        return;
    }

    int mx = (x1 + x2) >> 1, my = (y1 + y2) >> 1;
    build(4 * p + 1, x1, y1, mx, my);
    build(4 * p + 2, x1, my + 1, mx, y2);
    build(4 * p + 3, mx + 1, y1, x2, my);
    build(4 * p + 4, mx + 1, my + 1, x2, y2);
    pushUp(p);
}

int query(int p, int x1, int y1, int x2, int y2, int qx1, int qy1, int qx2, int qy2)
{
    if (x1 > x2 || y1 > y2) return -INF;
    if (x2 < qx1 || y2 < qy1 || x1 > qx2 || y1 > qy2) return -INF;
    if (qx1 <= x1 && x2 <= qx2 && qy1 <= y1 && y2 <= qy2) return st[p];

    int mx = (x1 + x2) >> 1, my = (y1 + y2) >> 1;
    int q1 = query(4 * p + 1, x1, y1, mx, my, qx1, qy1, qx2, qy2);
    int q2 = query(4 * p + 2, x1, my + 1, mx, y2, qx1, qy1, qx2, qy2);
    int q3 = query(4 * p + 3, mx + 1, y1, x2, my, qx1, qy1, qx2, qy2);
    int q4 = query(4 * p + 4, mx + 1, my + 1, x2, y2, qx1, qy1, qx2, qy2);
    return max(max(q1, q2), max(q3, q4));
}

void update(int p, int x1, int y1, int x2, int y2, int ux, int uy, int v)
{
    if (x1 > x2 || y1 > y2) return;
    if (x2 < ux || y2 < uy || x1 > ux || y1 > uy) return;
    if (x1 == x2 && y1 == y2 && x1 == ux && y1 == uy) { st[p] = v; return; }

    int mx = (x1 + x2) >> 1, my = (y1 + y2) >> 1;
    update(4 * p + 1, x1, y1, mx, my, ux, uy, v);
    update(4 * p + 2, x1, my + 1, mx, y2, ux, uy, v);
    update(4 * p + 3, mx + 1, y1, x2, my, ux, uy, v);
    update(4 * p + 4, mx + 1, my + 1, x2, y2, ux, uy, v);
    pushUp(p);
}

int main(int argc, char *argv[])
{
    return 0;
}
