// Average
// UVa ID: 1451
// Verdict: Accepted
// Submission Date: 2019-07-31
// UVa Run Time: 0.100s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

struct point { long long x, y; } P[MAXN];

long long cp(point &a, point &b, point &c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cwOrCollinear(int a, int b, int c)
{
    return cp(P[a], P[b], P[c]) <= 0;
}

bool ccwOrCollinear(int a, int b, int c)
{
    return cp(P[a], P[b], P[c]) >= 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, L, ai, si, head, rear, Q[MAXN];
    P[0].x = P[0].y = 0;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        point maxK, k;
        cin >> N >> L;
        si = 0;
        char ai;
        for (int i = 1; i <= N; i++) {
            cin >> ai;
            si += (ai - '0');
            P[i].x = i, P[i].y = si;
        }
        maxK.x = N, maxK.y = si;
        head = 0, rear = 0;
        int start = 0, end = N;
        for (int i = 0; i + L <= N; i++) {
            while (head + 2 <= rear && cwOrCollinear(Q[rear - 2], Q[rear - 1], i)) rear--;
            Q[rear++] = i;
            while (head + 2 <= rear && ccwOrCollinear(Q[head], Q[head + 1], i + L)) head++;
            k.x = i + L - Q[head], k.y = P[i + L].y - P[Q[head]].y;
            if ((maxK.y * k.x < maxK.x * k.y) ||
                ((maxK.y * k.x == maxK.x * k.y) && (i + L - Q[head] < end - start)))
            {
                maxK = k;
                start = Q[head], end = i + L;
            }
        }
        cout << (start + 1) << ' ' << end << '\n';
    }
    return 0;
}
