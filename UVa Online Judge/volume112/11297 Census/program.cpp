// Census
// UVa ID: 11297
// Verdict: Accepted
// Submission Date: 2019-01-12
// UVa Run Time: 0.400s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct node
{
    int high, low;
    node* children[4];
};

struct data { int high, low; };

int city[512][512];

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

node* build(int r1, int c1, int r2, int c2)
{
    if (r1 > r2 || c1 > c2) return NULL;
    if (r1 == r2 && c1 == c2)
    {
        node *nd = getNode();
        nd->high = nd->low = city[r1][c1];
        return nd;
    }

    node *nd = getNode();
    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    nd->children[0] = build(r1, c1, mr, mc);
    nd->children[1] = build(r1, mc + 1, mr, c2);
    nd->children[2] = build(mr + 1, c1, r2, mc);
    nd->children[3] = build(mr + 1, mc + 1, r2, c2);
    pushUp(nd);

    return nd;
}

void update(node *nd, int r1, int c1, int r2, int c2, int ur1, int uc1, int v)
{
    if (r1 > r2 || c1 > c2) return;
    if (r1 == r2 && c1 == c2 && r1 == ur1 && c1 == uc1) nd->high = v, nd->low = v;
    else
    {
        int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
        if (ur1 >= r1 && ur1 <= mr && uc1 >= c1 && uc1 <= mc)
            update(nd->children[0], r1, c1, mr, mc, ur1, uc1, v);
        else if (ur1 >= r1 && ur1 <= mr && uc1 >= mc + 1 && uc1 <= c2)
            update(nd->children[1], r1, mc + 1, mr, c2, ur1, uc1, v);
        else if (ur1 >= mr + 1 && ur1 <= r2 && uc1 >= c1 && uc1 <= mc)
            update(nd->children[2], mr + 1, c1, r2, mc, ur1, uc1, v);
        else if (ur1 >= mr + 1 && ur1 <= r2 && uc1 >= mc + 1 && uc1 <= c2)
            update(nd->children[3], mr + 1, mc + 1, r2, c2, ur1, uc1, v);
        pushUp(nd);
    }
}

data query(node *nd, int r1, int c1, int r2, int c2, int qr1, int qc1, int qr2, int qc2)
{
    if (r1 > r2 || c1 > c2) return data{-INF, INF};
    if (r2 < qr1 || c2 < qc1 || r1 > qr2 || c1 > qc2) return data{-INF, INF};
    if (qr1 <= r1 && r2 <= qr2 && qc1 <= c1 && c2 <= qc2) return data{nd->high, nd->low};

    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    data q1 = query(nd->children[0], r1, c1, mr, mc, qr1, qc1, qr2, qc2);
    data q2 = query(nd->children[1], r1, mc + 1, mr, c2, qr1, qc1, qr2, qc2);
    data q3 = query(nd->children[2], mr + 1, c1, r2, mc, qr1, qc1, qr2, qc2);
    data q4 = query(nd->children[3], mr + 1, mc + 1, r2, c2, qr1, qc1, qr2, qc2);
    int high = max(max(q1.high, q2.high), max(q3.high, q4.high));
    int low = min(min(q1.low, q2.low), min(q3.low, q4.low));

    return data{high, low};
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    cin >> n;
        
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> city[i][j];

    node *root = build(0, 0, n - 1, n - 1);

    int q, x1, y1, x2, y2, v;
    char action;

    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> action;
        if (action == 'c')
        {
            cin >> x1 >> y1 >> v;
            update(root, 0, 0, n - 1, n - 1, x1 - 1, y1 - 1, v);
        }
        else
        {
            cin >> x1 >> y1 >> x2 >> y2;
            x2 = min(x2, n), y2 = min(y2, n);
            data r = query(root, 0, 0, n - 1, n - 1, x1 - 1, y1 - 1, x2 - 1, y2 - 1);
            cout << r.high << ' ' << r.low << '\n';
        }
    }

    return 0;
}
