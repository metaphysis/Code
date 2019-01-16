// Census
// UVa ID: 11297
// Verdict: Accepted
// Submission Date: 2019-01-12
// UVa Run Time: 0.280s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 512, INF = 0x7f7f7f7f;

int data[MAXN][MAXN];
pair<int, int> st[4 * MAXN * MAXN];

void pushUp(int p)
{
    int high = -INF, low = INF;
    for (int i = 1; i <= 4; i++) {
        high = max(high, st[4 * p + i].first);
        low = min(low, st[4 * p + i].second);
    }
    st[p].first = high, st[p].second = low;
}

void build(int p, int r1, int c1, int r2, int c2)
{
    if (r1 > r2 || c1 > c2) {
        st[p] = make_pair(-INF, INF);
        return;
    }
    if (r1 == r2 && c1 == c2) {
        st[p] = make_pair(data[r1][c1], data[r1][c1]);
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
    if (r1 == r2 && c1 == c2 && r1 == ur && c1 == uc) st[p] = make_pair(v, v);
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

pair<int, int> query(int p, int r1, int c1, int r2, int c2, int qr1, int qc1, int qr2, int qc2)
{
    if (r1 > r2 || c1 > c2) return make_pair(-INF, INF);
    if (r2 < qr1 || c2 < qc1 || r1 > qr2 || c1 > qc2) return make_pair(-INF, INF);
    if (qr1 <= r1 && r2 <= qr2 && qc1 <= c1 && c2 <= qc2) return st[p];

    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    pair<int, int> q1 = query(4 * p + 1, r1, c1, mr, mc, qr1, qc1, qr2, qc2);
    pair<int, int> q2 = query(4 * p + 2, r1, mc + 1, mr, c2, qr1, qc1, qr2, qc2);
    pair<int, int> q3 = query(4 * p + 3, mr + 1, c1, r2, mc, qr1, qc1, qr2, qc2);
    pair<int, int> q4 = query(4 * p + 4, mr + 1, mc + 1, r2, c2, qr1, qc1, qr2, qc2);
    int high = max(max(q1.first, q2.first), max(q3.first, q4.first));
    int low = min(min(q1.second, q2.second), min(q3.second, q4.second));

    return make_pair(high, low);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    cin >> n;
        
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> data[i][j];

    build(0, 0, 0, n - 1, n - 1);

    int q, x1, y1, x2, y2, v;
    char action;

    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> action;
        if (action == 'c')
        {
            cin >> x1 >> y1 >> v;
            update(0, 0, 0, n - 1, n - 1, x1 - 1, y1 - 1, v);
        }
        else
        {
            cin >> x1 >> y1 >> x2 >> y2;
            x2 = min(x2, n), y2 = min(y2, n);
            pair<int, int> r = query(0, 0, 0, n - 1, n - 1, x1 - 1, y1 - 1, x2 - 1, y2 - 1);
            cout << r.first << ' ' << r.second << '\n';
        }
    }

    return 0;
}
