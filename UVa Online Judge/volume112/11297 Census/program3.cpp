// Census
// UVa ID: 11297
// Verdict: Accepted
// Submission Date: 2019-01-15
// UVa Run Time: 0.060s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 512, INF = 0x7f7f7f7f;

#define LCHILD(x) ((x << 1) | 1)
#define RCHILD(x) ((x + 1) << 1)

int n, m, grid[MAXN][MAXN];

struct node { int high, low; } st[4 * MAXN][4 * MAXN];

node combine(node a, node b) { return node{max(a.high, b.high), min(a.low, b.low)}; }

void buildY(int px, int lx, int rx, int py, int ly, int ry)
{
    if (ly == ry) {
        if (lx == rx) st[px][py] = node{grid[lx][ly], grid[lx][ly]};
        else st[px][py] = combine(st[LCHILD(px)][py], st[RCHILD(px)][py]);
    } else {
        int my = (ly + ry) >> 1;
        buildY(px, lx, rx, LCHILD(py), ly, my);
        buildY(px, lx, rx, RCHILD(py), my + 1, ry);
        st[px][py] = combine(st[px][LCHILD(py)], st[px][RCHILD(py)]);
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
        if (lx == rx) st[px][py] = node{value, value};
        else st[px][py] = combine(st[LCHILD(px)][py], st[RCHILD(px)][py]);
    } else {
        int my = (ly + ry) >> 1;
        if (y <= my)
            updateY(px, lx, rx, LCHILD(py), ly, my, x, y, value);
        else
            updateY(px, lx, rx, RCHILD(py), my + 1, ry, x, y, value);
        st[px][py] = combine(st[px][LCHILD(py)], st[px][RCHILD(py)]);
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

node queryY(int px, int py, int ly, int ry, int qly, int qry)
{
    if (ly > qry || ry < qly) return node{-INF, INF};
    if (qly <= ly && ry <= qry) return st[px][py];
    int my = (ly + ry) >> 1;
    node q1 = queryY(px, LCHILD(py), ly, my, qly, qry);
    node q2 = queryY(px, RCHILD(py), my + 1, ry, qly, qry);
    return combine(q1, q2);
}

node queryX(int px, int lx, int rx, int qlx, int qly, int qrx, int qry)
{
    if (lx > qrx || rx < qlx) return node{-INF, INF};
    if (qlx <= lx && rx <= qrx) return queryY(px, 0, 0, m - 1, qly, qry);
    int mx = (lx + rx) >> 1;
    node q1 = queryX(LCHILD(px), lx, mx, qlx, qly, qrx, qry);
    node q2 = queryX(RCHILD(px), mx + 1, rx, qlx, qly, qrx, qry);
    return combine(q1, q2);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    m = n;
    buildX(0, 0, n - 1);

    int q, x1, y1, x2, y2, v;
    char action;

    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> action;
        if (action == 'c')
        {
            cin >> x1 >> y1 >> v;
            updateX(0, 0, n - 1, x1 - 1, y1 - 1, v);
        }
        else
        {
            cin >> x1 >> y1 >> x2 >> y2;
            x2 = min(x2, n), y2 = min(y2, n);
            node r = queryX(0, 0, n - 1, x1 - 1, y1 - 1, x2 - 1, y2 - 1);
            cout << r.high << ' ' << r.low << '\n';
        }
    }

    return 0;
}
