// Census
// UVa ID: 11297
// Verdict: Accepted
// Submission Date: 2019-01-12
// UVa Run Time: 0.450s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 512, INF = 0x7f7f7f7f;

struct rectangle
{
    int r1, c1, r2, c2;
    rectangle(int r1 = 0, int c1 = 0, int r2 = 0, int c2 = 0): r1(r1), c1(c1), r2(r2), c2(c2) {}
    bool isBad() { return r1 > r2 || c1 > c2; }
    bool isCell() { return r1 == r2 && c1 == c2; }
    bool contains(int r, int c) { return r1 <= r && r <= r2 && c1 <= c && c <= c2; }
    bool contains(rectangle q) { return r1 <= q.r1 && q.r2 <= r2 && c1 <= q.c1 && q.c2 <= c2; }
    bool awayFrom(rectangle q) { return r1 > q.r2 || c1 > q.c2 || r2 < q.r1 || c2 < q.c1; }
    rectangle LU() { return rectangle(r1, c1, (r1 + r2) >> 1, (c1 + c2) >> 1); }
    rectangle RU() { return rectangle(r1, ((c1 + c2) >> 1) + 1, (r1 + r2) >> 1, c2); }
    rectangle LB() { return rectangle(((r1 + r2) >> 1) + 1, c1, r2, (c1 + c2) >> 1); }
    rectangle RB() { return rectangle(((r1 + r2) >> 1) + 1, ((c1 + c2) >> 1) + 1, r2, c2); }
};

struct node
{
    int high, low;
    node* children[4];
};

struct data { int high, low; };

int grid[MAXN][MAXN];

node* getNode()
{
    node *nd = new node;
    nd->high = -INF, nd->low = INF;
    for (int i = 0; i < 4; i++) nd->children[i] = NULL;
    return nd;
}

void pushUp(node *nd)
{
    int high = -INF, low = INF;
    for (int i = 0; i < 4; i++) {
        if (nd->children[i] == NULL) continue;
        high = max(high, nd->children[i]->high);
        low = min(low, nd->children[i]->low);
    }
    nd->high = high, nd->low = low;
}

node* build(rectangle r)
{
    if (r.isBad()) return NULL;
    if (r.isCell()) {
        node *nd = getNode();
        nd->high = nd->low = grid[r.r1][r.c1];
        return nd;
    }

    node *nd = getNode();

    nd->children[0] = build(r.LU());
    nd->children[1] = build(r.RU());
    nd->children[2] = build(r.LB());
    nd->children[3] = build(r.RB());

    pushUp(nd);

    return nd;
}

data query(node *nd, rectangle r, rectangle qr)
{
    if (r.isBad()) return data{-INF, INF};
    if (r.awayFrom(qr)) return data{-INF, INF};
    if (qr.contains(r)) return data{nd->high, nd->low};

    data q1 = query(nd->children[0], r.LU(), qr);
    data q2 = query(nd->children[1], r.RU(), qr);
    data q3 = query(nd->children[2], r.LB(), qr);
    data q4 = query(nd->children[3], r.RB(), qr);
    int high = max(max(q1.high, q2.high), max(q3.high, q4.high));
    int low = min(min(q1.low, q2.low), min(q3.low, q4.low));

    return data{high, low};
}

void update(node *nd, rectangle r, int ur1, int uc1, int v)
{
    if (r.isBad()) return;
    if (r.isCell() && r.contains(ur1, uc1)) nd->high = v, nd->low = v;
    else {
        if (r.LU().contains(ur1, uc1)) update(nd->children[0], r.LU(), ur1, uc1, v);
        else if (r.RU().contains(ur1, uc1)) update(nd->children[1], r.RU(), ur1, uc1, v);
        else if (r.LB().contains(ur1, uc1)) update(nd->children[2], r.LB(), ur1, uc1, v);
        else if (r.RB().contains(ur1, uc1)) update(nd->children[3], r.RB(), ur1, uc1, v);
        pushUp(nd);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    cin >> n;
        
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    node *root = build(rectangle(0, 0, n - 1, n - 1));

    int q, x1, y1, x2, y2, v;
    char action;

    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> action;
        if (action == 'c')
        {
            cin >> x1 >> y1 >> v;
            update(root, rectangle(0, 0, n - 1, n - 1), x1 - 1, y1 - 1, v);
        }
        else
        {
            cin >> x1 >> y1 >> x2 >> y2;
            x2 = min(x2, n), y2 = min(y2, n);
            data r = query(root, rectangle(0, 0, n - 1, n - 1), rectangle(x1 - 1, y1 - 1, x2 - 1, y2 - 1));
            cout << r.high << ' ' << r.low << '\n';
        }
    }

    return 0;
}
