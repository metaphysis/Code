// Ants
// UVa ID: 1411
// Verdict: Accepted
// Submission Date: 2019-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 210;

struct point { int x, y, idx, type; } ps[MAXN];

point pr;
int link[MAXN];

bool cmp1(point &a, point &b)
{
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

bool cmp2(point &a, point &b)
{
    return (a.x - pr.x) * (b.y - pr.y) - (b.x - pr.x) * (a.y - pr.y) > 0;
}

void match(int l, int r)
{
    if (l >= r) return;
    sort(ps + l, ps + r + 1, cmp1);
    pr = ps[l];
    sort(ps + l + 1, ps + r + 1, cmp2);
    int s1 = 0, s2 = 0;
    if (pr.type == 0) s1 = 1;
    else s2 = 1;
    for (int i = l + 1; i <= r; i++)
    {
        if (ps[i].type == 0) s1++;
        else s2++;
        if (s1 == s2)
        {
            if (pr.type == 0) link[pr.idx] = ps[i].idx;
            else link[ps[i].idx] = pr.idx;
            match(l + 1, i - 1);
            match(i + 1, r);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;

    while (cin >> n)
    {
        if (cases++) cout << '\n';
        for (int i = 0; i < n; i++)
        {
            cin >> ps[i].x >> ps[i].y;
            ps[i].idx = i + 1;
            ps[i].type = 0;
        }
        for (int i = 0; i < n; i++)
        {
            cin >> ps[i + n].x >> ps[i + n].y;
            ps[i + n].idx = i + 1;
            ps[i + n].type = 1;
        }
        match(0, 2 * n - 1);
        for (int i = 1; i <= n; i++) cout << link[i] << '\n';
    }

    return 0;
}
