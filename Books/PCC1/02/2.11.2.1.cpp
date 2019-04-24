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

void build(int p, int r1, int c1, int r2, int c2)
{
    if (r1 > r2 || c1 > c2) {
        st[p] = -INF;
        return;
    }
    if (r1 == r2 && c1 == c2) {
        st[p] = data[r1][c1];
        return;
    }

    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    build(4 * p + 1, r1, c1, mr, mc);
    build(4 * p + 2, r1, mc + 1, mr, c2);
    build(4 * p + 3, mr + 1, c1, r2, mc);
    build(4 * p + 4, mr + 1, mc + 1, r2, c2);
    pushUp(p);
}

void update(int p, int r1, int c1, int r2, int c2, int ur, int uc, int v)
{
    if (r1 > r2 || c1 > c2) return;
    if (r1 == r2 && c1 == c2 && r1 == ur && c1 == uc) st[p] = v;
    else
    {
        int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
        if (ur >= r1 && ur <= mr && uc >= c1 && uc <= mc)
            update(4 * p + 1, r1, c1, mr, mc, ur, uc, v);
        else if (ur >= r1 && ur <= mr && uc >= mc + 1 && uc <= c2)
            update(4 * p + 2, r1, mc + 1, mr, c2, ur, uc, v);
        else if (ur >= mr + 1 && ur <= r2 && uc >= c1 && uc <= mc)
            update(4 * p + 3, mr + 1, c1, r2, mc, ur, uc, v);
        else if (ur >= mr + 1 && ur <= r2 && uc >= mc + 1 && uc <= c2)
            update(4 * p + 4, mr + 1, mc + 1, r2, c2, ur, uc, v);
        pushUp(p);
    }
}

int query(int p, int r1, int c1, int r2, int c2, int qr1, int qc1, int qr2, int qc2)
{
    if (r1 > r2 || c1 > c2) return -INF;
    if (r2 < qr1 || c2 < qc1 || r1 > qr2 || c1 > qc2) return -INF;
    if (qr1 <= r1 && r2 <= qr2 && qc1 <= c1 && c2 <= qc2) return st[p];

    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    int q1 = query(4 * p + 1, r1, c1, mr, mc, qr1, qc1, qr2, qc2);
    int q2 = query(4 * p + 2, r1, mc + 1, mr, c2, qr1, qc1, qr2, qc2);
    int q3 = query(4 * p + 3, mr + 1, c1, r2, mc, qr1, qc1, qr2, qc2);
    int q4 = query(4 * p + 4, mr + 1, mc + 1, r2, c2, qr1, qc1, qr2, qc2);
    return max(max(q1, q2), max(q3, q4));
}

int main(int argc, char *argv[])
{
    return 0;
}
