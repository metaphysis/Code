// Fast Matrix Operations
// UVa ID: 11992
// Verdict: Accepted
// Submission Date: 2017-10-30
// UVa Run Time: 0.240s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1000010, INF = 0x3f3f3f3f;

struct node { int sum, high, low; } qt[4 * MAXV];

void build(int p, int r1, int c1, int r2, int c2)
{
    if (r2 < r1 || c2 < c1) return;
    if (r1 == r2 && c1 == c2) qt[p].sum = qt[p].high = qt[p].low = 0;
    else {
        int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;

        build((p << 2) + 1, r1, c1, mr, mc);
        build((p << 2) + 2, r1, mc + 1, mr, c2);
        build((p << 2) + 3, mr + 1, c1, r2, mc);
        build((p << 2) + 4, mr + 1, mc + 1, r2, c2);

        qt[p].sum = qt[(p << 2) + 1].sum;
        qt[p].high = qt[(p << 2) + 1].high;
        qt[p].low = qt[(p << 2) + 1].low;
        for (int i = 2; i <= 4; i++)
        {
            qt[p].sum += qt[(p << 2) + i].sum;
            qt[p].high = max(qt[p].high, qt[(p << 2) + i].high);
            qt[p].low = min(qt[p].low, qt[(p << 2) + i].low);
        }
    }
}

node query(int p, int r1, int c1, int r2, int c2, int qr1, int qc1, int qr2, int qc2)
{
    if (r1 > r2 || c1 > c2) return node{0, -INF, INF};
    if (r2 < qr1 || c2 < qc1 || r1 > qr2 || c1 > qc2) return node{0, -INF, INF};
    if (qr1 <= r1 && r2 <= qr2 && qc1 <= c1 && c2 <= qc2) return node{qt[p].sum, qt[p].high, qt[p].low};

    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    node q1 = query((p << 2) + 1, r1, c1, mr, mc, qr1, qc1, qr2, qc2);
    node q2 = query((p << 2) + 2, r1, mc + 1, mr, c2, qr1, qc1, qr2, qc2);
    node q3 = query((p << 2) + 3, mr + 1, c1, r2, mc, qr1, qc1, qr2, qc2);
    node q4 = query((p << 2) + 4, mr + 1, mc + 1, r2, c2, qr1, qc1, qr2, qc2);

    int sum = q1.sum + q2.sum + q3.sum + q4.sum;
    int high = max(max(q1.high, q2.high), max(q3.high, q4.high));
    int low = min(min(q1.low, q2.low), min(q3.low, q4.low));
    
    return node{sum, high, low};
}

void update(int p, int r1, int c1, int r2, int c2, int ur1, int uc1, int v, int add)
{
    if (r2 < r1 || c2 < c1) return;
    if (r1 == r2 && c1 == c2 && r1 == ur1 && c1 == uc1) 
    {
        if (add)
        {
            qt[p].sum += v;
            qt[p].high += v;
            qt[p].low += v;
        }
        else
        {
            qt[p].sum = v;
            qt[p].high = v;
            qt[p].low = v;
        }
    }
    else {
        int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
        if (ur1 >= r1 && ur1 <= mr && uc1 >= c1 && uc1 <= mc)
            update((p << 2) + 1, r1, c1, mr, mc, ur1, uc1, v, add);
        else if (ur1 >= r1 && ur1 <= mr && uc1 >= mc + 1 && uc1 <= c2)
            update((p << 2) + 2, r1, mc + 1, mr, c2, ur1, uc1, v, add);
        else if (ur1 >= mr + 1 && ur1 <= r2 && uc1 >= c1 && uc1 <= mc)
            update((p << 2) + 3, mr + 1, c1, r2, mc, ur1, uc1, v, add);
        else if (ur1 >= mr + 1 && ur1 <= r2 && uc1 >= mc + 1 && uc1 <= c2)
            update((p << 2) + 4, mr + 1, mc + 1, r2, c2, ur1, uc1, v, add);

        qt[p].sum = qt[(p << 2) + 1].sum;
        qt[p].high = qt[(p << 2) + 1].high;
        qt[p].low = qt[(p << 2) + 1].low;
        for (int i = 2; i <= 4; i++)
        {
            qt[p].sum += qt[(p << 2) + i].sum;
            qt[p].high = max(qt[p].high, qt[(p << 2) + i].high);
            qt[p].low = min(qt[p].low, qt[(p << 2) + i].low);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int r, c, m;
    while (cin >> r >> c >> m)
    {
        r = c = 32;
        build(0, 0, 0, r - 1, c - 1);
        int q, x1, y1, x2, y2, v;
        for (int z = 1; z <= m; z++)
        {
            cin >> q;
            if (q == 1)
            {
                cin >> x1 >> y1 >> x2 >> y2 >> v;
                for (int i = x1; i <= x2; i++)
                    for (int j = y1; j <= y2; j++)
                        update(0, 0, 0, r - 1, c - 1, i - 1, j - 1, v, 1);
            }
            else if (q == 2)
            {
                cin >> x1 >> y1 >> x2 >> y2 >> v;
                for (int i = x1; i <= x2; i++)
                    for (int j = y1; j <= y2; j++)
                        update(0, 0, 0, r - 1, c - 1, i - 1, j - 1, v, 0);
            }
            else
            {
                cin >> x1 >> y1 >> x2 >> y2;
                node nd = query(0, 0, 0, r - 1, c - 1, x1 - 1, y1 - 1, x2 - 1, y2 - 1);
                cout << nd.sum << ' ' << nd.low << ' ' << nd.high << '\n';
            }
        }
        break;
    }

    return 0;
}
