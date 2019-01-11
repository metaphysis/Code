// Census
// UVa ID: 11297
// Verdict: Accepted
// Submission Date: 2017-10-30
// UVa Run Time: 0.240s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 250000, INF = 0x3f3f3f3f;

struct node { int high, low; } qt[4 * MAXV];
int city[512][512];

void build(int p, int r1, int c1, int r2, int c2)
{
    if (r2 < r1 || c2 < c1) return;
    if (r1 == r2 && c1 == c2) qt[p].high = qt[p].low = city[r1][c1];
    else {
        int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;

        build((p << 2) + 1, r1, c1, mr, mc);
        build((p << 2) + 2, r1, mc + 1, mr, c2);
        build((p << 2) + 3, mr + 1, c1, r2, mc);
        build((p << 2) + 4, mr + 1, mc + 1, r2, c2);

        qt[p].high = qt[(p << 2) + 1].high, qt[p].low = qt[(p << 2) + 1].low;
        for (int i = 2; i <= 4; i++)
        {
            qt[p].high = max(qt[p].high, qt[(p << 2) + i].high);
            qt[p].low = min(qt[p].low, qt[(p << 2) + i].low);
        }
    }
}

pair<int, int> query(int p, int r1, int c1, int r2, int c2, int qr1, int qc1, int qr2, int qc2)
{
    if (r2 < qr1 || c2 < qc1 || r1 > qr2 || c1 > qc2) return make_pair(-INF, INF);
    if (qr1 <= r1 && r2 <= qr2 && qc1 <= c1 && c2 <= qc2) return make_pair(qt[p].high, qt[p].low);

    int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
    pair<int, int> q1 = query((p << 2) + 1, r1, c1, mr, mc, qr1, qc1, qr2, qc2);
    pair<int, int> q2 = query((p << 2) + 2, r1, mc + 1, mr, c2, qr1, qc1, qr2, qc2);
    pair<int, int> q3 = query((p << 2) + 3, mr + 1, c1, r2, mc, qr1, qc1, qr2, qc2);
    pair<int, int> q4 = query((p << 2) + 4, mr + 1, mc + 1, r2, c2, qr1, qc1, qr2, qc2);
    
    int high = max(max(q1.first, q2.first), max(q3.first, q4.first));
    int low = min(min(q1.second, q2.second), min(q3.second, q4.second));
    
    return make_pair(high, low);
}

void update(int p, int r1, int c1, int r2, int c2, int ur1, int uc1, int v)
{
    if (r2 < r1 || c2 < c1) return;
    if (r1 == r2 && c1 == c2 && r1 == ur1 && c1 == uc1) qt[p].high = qt[p].low = v;
    else {
        int mr = (r1 + r2) >> 1, mc = (c1 + c2) >> 1;
        if (ur1 >= r1 && ur1 <= mr && uc1 >= c1 && uc1 <= mc)
            update((p << 2) + 1, r1, c1, mr, mc, ur1, uc1, v);
        else if (ur1 >= r1 && ur1 <= mr && uc1 >= mc + 1 && uc1 <= c2)
            update((p << 2) + 2, r1, mc + 1, mr, c2, ur1, uc1, v);
        else if (ur1 >= mr + 1 && ur1 <= r2 && uc1 >= c1 && uc1 <= mc)
            update((p << 2) + 3, mr + 1, c1, r2, mc, ur1, uc1, v);
        else if (ur1 >= mr + 1 && ur1 <= r2 && uc1 >= mc + 1 && uc1 <= c2)
            update((p << 2) + 4, mr + 1, mc + 1, r2, c2, ur1, uc1, v);

        qt[p].high = qt[(p << 2) + 1].high, qt[p].low = qt[(p << 2) + 1].low;
        for (int i = 2; i <= 4; i++)
        {
            qt[p].high = max(qt[p].high, qt[(p << 2) + i].high);
            qt[p].low = min(qt[p].low, qt[(p << 2) + i].low);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    cin >> n;
        
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> city[i][j];

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
            //x2 = min(x2, n), y2 = min(y2, n);
            pair<int, int> r = query(0, 0, 0, n - 1, n - 1, x1 - 1, y1 - 1, x2 - 1, y2 - 1);
            cout << r.first << ' ' << r.second << '\n';
        }
    }

    return 0;
}
