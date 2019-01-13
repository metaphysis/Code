// Fast Matrix Operations
// UVa ID: 11992
// Verdict: Accepted
// Submission Date: 2019-01-12
// UVa Run Time: 0.600s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct NODE
{
    int sum, high, low, tag;
    NODE* children[4];
};

struct QUERY
{
    int sum, high, low;
};

NODE* getNode()
{
    NODE *nd = new NODE;
    nd->sum = 0, nd->high = -INF, nd->low = INF, nd->tag = 0;
    for (int i = 0; i < 4; i++) nd->children[i] = NULL;
    return nd;
}

void commit(NODE *nd, int r1, int c1, int r2, int c2, int utag)
{
    if (nd == NULL) return;

    if (utag > 0)
    {
        if (nd->tag >= 0)
        {
            nd->tag += utag;
            nd->sum += (r2 - r1 + 1) * (c2 - c1 + 1) * utag, nd->high += utag, nd->low += utag;
        }
        else
        {
            nd->tag -= utag;
            int delta = abs(nd->tag);
            nd->sum = (r2 - r1 + 1) * (c2 - c1 + 1) * delta, nd->high = delta, nd->low = delta;
        }
    }
    else
    {
        nd->tag = utag;
        int delta = abs(utag);
        nd->sum = (r2 - r1 + 1) * (c2 - c1 + 1) * delta, nd->high = delta, nd->low = delta;
    }
}

void pushDown(NODE *nd, int r1, int c1, int r2, int c2)
{
    if (nd->tag != 0)
    {
        int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
        commit(nd->children[0], r1, c1, mr, mc, nd->tag);
        commit(nd->children[1], r1, mc + 1, mr, c2, nd->tag);
        commit(nd->children[2], mr + 1, c1, r2, mc, nd->tag);
        commit(nd->children[3], mr + 1, mc + 1, r2, c2, nd->tag);
        nd->tag = 0;
    }
}

void pushUp(NODE *nd)
{
    int sum = 0, high = -INF, low = INF;
    for (int i = 0; i < 4; i++)
    {
        if (nd->children[i] == NULL) continue;
        sum += nd->children[i]->sum;
        high = max(high, nd->children[i]->high);
        low = min(low, nd->children[i]->low);
    }
    nd->sum = sum, nd->high = high, nd->low = low;    
}

NODE* build(int r1, int c1, int r2, int c2)
{
    if (r1 > r2 || c1 > c2) return NULL;
    if (r1 == r2 && c1 == c2)
    {
        NODE *nd = getNode();
        nd->sum = nd->high = nd->low = 0;
        return nd;
    }

    NODE *nd = getNode();

    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    nd->children[0] = build(r1, c1, mr, mc);
    nd->children[1] = build(r1, mc + 1, mr, c2);
    nd->children[2] = build(mr + 1, c1, r2, mc);
    nd->children[3] = build(mr + 1, mc + 1, r2, c2);

    pushUp(nd);

    return nd;
}

QUERY query(NODE *nd, int r1, int c1, int r2, int c2, int qr1, int qc1, int qr2, int qc2)
{
    if (r1 > r2 || c1 > c2) return QUERY{0, -INF, INF};
    if (r2 < qr1 || c2 < qc1 || r1 > qr2 || c1 > qc2) return QUERY{0, -INF, INF};
    if (qr1 <= r1 && r2 <= qr2 && qc1 <= c1 && c2 <= qc2) return QUERY{nd->sum, nd->high, nd->low};

    pushDown(nd, r1, c1, r2, c2);

    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    QUERY q1 = query(nd->children[0], r1, c1, mr, mc, qr1, qc1, qr2, qc2);
    QUERY q2 = query(nd->children[1], r1, mc + 1, mr, c2, qr1, qc1, qr2, qc2);
    QUERY q3 = query(nd->children[2], mr + 1, c1, r2, mc, qr1, qc1, qr2, qc2);
    QUERY q4 = query(nd->children[3], mr + 1, mc + 1, r2, c2, qr1, qc1, qr2, qc2);
    int sum = q1.sum + q2.sum + q3.sum + q4.sum;
    int high = max(max(q1.high, q2.high), max(q3.high, q4.high));
    int low = min(min(q1.low, q2.low), min(q3.low, q4.low));

    return QUERY{sum, high, low};
}

void update(NODE *nd, int r1, int c1, int r2, int c2, int ur1, int uc1, int ur2, int uc2, int utag)
{
    if (r1 > r2 || c1 > c2) return;
    if (r2 < ur1 || c2 < uc1 || r1 > ur2 || c1 > uc2) return;
    if (ur1 <= r1 && r2 <= ur2 && uc1 <= c1 && c2 <= uc2) 
    {
        commit(nd, r1, c1, r2, c2, utag);
        return;
    }

    pushDown(nd, r1, c1, r2, c2);

    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    update(nd->children[0], r1, c1, mr, mc, ur1, uc1, ur2, uc2, utag);
    update(nd->children[1], r1, mc + 1, mr, c2, ur1, uc1, ur2, uc2, utag);
    update(nd->children[2], mr + 1, c1, r2, mc, ur1, uc1, ur2, uc2, utag);
    update(nd->children[3], mr + 1, mc + 1, r2, c2, ur1, uc1, ur2, uc2, utag);

    pushUp(nd);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int r, c, m;
    while (cin >> r >> c >> m)
    {
        NODE *root = build(0, 0, r - 1, c - 1);
        int q, x1, y1, x2, y2, v;
        for (int z = 1; z <= m; z++)
        {
            cin >> q;
            if (q == 1)
            {
                cin >> x1 >> y1 >> x2 >> y2 >> v;
                update(root, 0, 0, r - 1, c - 1, x1 - 1, y1 - 1, x2 - 1, y2 - 1, v);
            }
            else if (q == 2)
            {
                cin >> x1 >> y1 >> x2 >> y2 >> v;
                update(root, 0, 0, r - 1, c - 1, x1 - 1, y1 - 1, x2 - 1, y2 - 1, -v);
            }
            else
            {
                cin >> x1 >> y1 >> x2 >> y2;
                QUERY nd = query(root, 0, 0, r - 1, c - 1, x1 - 1, y1 - 1, x2 - 1, y2 - 1);
                cout << nd.sum << ' ' << nd.low << ' ' << nd.high << '\n';
            }
        }
    }

    return 0;
}
