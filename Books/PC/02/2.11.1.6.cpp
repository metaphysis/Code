#include <bits/stdc++.h>

using namespace std;

const int MAXN = 512, INF = 0x7f7f7f7f;

#define LCHILD(x) (((x) << 1) | 1)
#define RCHILD(x) (((x) + 1) << 1)

int n, m, data[MAXN][MAXN];

int st[4 * MAXN][4 * MAXN];

void buildY(int px, int lx, int rx, int py, int ly, int ry)
{
    if (ly == ry) {
        if (lx == rx) st[px][py] = data[lx][ly];
        else st[px][py] = max(st[LCHILD(px)][py], st[RCHILD(px)][py]);
    } else {
        int my = (ly + ry) >> 1;
        buildY(px, lx, rx, LCHILD(py), ly, my);
        buildY(px, lx, rx, RCHILD(py), my + 1, ry);
        st[px][py] = max(st[px][LCHILD(py)], st[px][RCHILD(py)]);
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

void updateY(int px, int lx, int rx, int py, int ly, int ry, int x, int y, int value)
{
    if (ly == ry) {
        if (lx == rx) st[px][py] = data[lx][ly];
        else st[px][py] = max(st[LCHILD(px)][py], st[RCHILD(px)][py]);
    } else {
        int my = (ly + ry) >> 1;
        if (y <= my)
            updateY(px, lx, rx, LCHILD(py), ly, my, x, y, value);
        else
            updateY(px, lx, rx, RCHILD(py), my + 1, ry, x, y, value);
        st[px][py] = max(st[px][LCHILD(py)], st[px][RCHILD(py)]);
    }
}

void updateX(int px, int lx, int rx, int x, int y, int value)
{
    if (lx != rx) {
        int mx = (lx + rx) >> 1;
        if (x <= mx)
            updateX(LCHILD(px), lx, mx, x, y, value);
        else
            updateX(RCHILD(px), mx + 1, rx, x, y, value);
    }
    updateY(px, lx, rx, 0, 0, m - 1, x, y, value);
}

int queryY(int px, int py, int ly, int ry, int qly, int qry)
{
    if (ly > qry || ry < qly) return -INF;
    if (qly <= ly && ry <= qry) return st[px][py];
    int my = (ly + ry) >> 1;
    int q1 = queryY(px, LCHILD(py), ly, my, qly, qry);
    int q2 = queryY(px, RCHILD(py), my + 1, ry, qly, qry);
    return max(q1, q2);
}

int queryX(int px, int lx, int rx, int qlx, int qly, int qrx, int qry)
{
    if (lx > qrx || rx < qlx) return -INF;
    if (qlx <= lx && rx <= qrx) return queryY(px, 0, 0, m - 1, qly, qry);
    int mx = (lx + rx) >> 1;
    int q1 = queryX(LCHILD(px), lx, mx, qlx, qly, qrx, qry);
    int q2 = queryX(RCHILD(px), mx + 1, rx, qlx, qly, qrx, qry);
    return max(q1, q2);
}

int main(int argc, char *argv[])
{
    return 0;
}
