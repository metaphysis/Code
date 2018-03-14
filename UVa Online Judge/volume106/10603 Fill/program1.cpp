// Fill
// UVa ID: 10603
// Verdict: Accepted
// Submission Date: 2018-02-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int a, b, c, d;
    edge (int a = 0, int b = 0, int c = 0, int d = 0): a(a), b(b), c(c), d(d) {}
};

int dist[201][201];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int a, b, c, d, dist[201][201], amount[201], INF = 0x7f7f7f7f;
    int aa, bb, cc;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> a >> b >> c >> d;

        memset(dist, 0x7f, sizeof(dist));
        memset(amount, 0x7f, sizeof(amount));

        queue<edge> q;
        q.push(edge(0, 0, c, 0));

        dist[0][0] = 0;
        amount[0] = amount[c] = 0;
        edge edges[6];

        while (!q.empty())
        {
            edge u = q.front(); q.pop();

            int cnt = 0;
            if (u.a)
            {
                if (u.a > (b - u.b))
                    edges[cnt++] = edge(u.a + u.b - b, b, u.c, b - u.b);
                else
                    edges[cnt++] = edge(0, u.b + u.a, u.c, u.a);
                if (u.a > (c - u.c))
                    edges[cnt++] = edge(u.a + u.c - c, u.b, c, c - u.c);
                else
                    edges[cnt++] = edge(0, u.b, u.c + u.a, u.a);
            }

            if (u.b)
            {
                if (u.b > (a - u.a))
                    edges[cnt++] = edge(a, u.b + u.a - a, u.c, a - u.a);
                else
                    edges[cnt++] = edge(u.a + u.b, 0, u.c, u.b);
                if (u.b > (c - u.c))
                    edges[cnt++] = edge(u.a, u.b + u.c - c, c, c - u.c);
                else
                    edges[cnt++] = edge(u.a, 0, u.c + u.b, u.b);
                
            }

            if (u.c)
            {
                if (u.c > (a - u.a))
                    edges[cnt++] = edge(a, u.b, u.c + u.a - a, a - u.a);
                else
                    edges[cnt++] = edge(u.a + u.c, u.b, 0, u.c);
                if (u.c > (b - u.b))
                    edges[cnt++] = edge(u.a, b, u.c + u.b - b, b - u.b);
                else
                    edges[cnt++] = edge(u.a, u.b + u.c, 0, u.c);
            }

            for (int k = 0; k < cnt; k++)
            {
                aa = edges[k].a, bb = edges[k].b, cc = edges[k].c;
                if (dist[aa][bb] > dist[u.a][u.b] + edges[k].d)
                {
                    dist[aa][bb] = dist[u.a][u.b] + edges[k].d;
                    amount[aa] = min(amount[aa], dist[aa][bb]);
                    amount[bb] = min(amount[bb], dist[aa][bb]);
                    amount[cc] = min(amount[cc], dist[aa][bb]);
                    q.push(edge(aa, bb, cc, dist[aa][bb]));
                }
            }
        }

        for (int i = min(d, c); i >= 0; i--)
            if (amount[i] != INF)
            {
                cout << amount[i] << ' ' << i << '\n';
                break;
            }
    }

    return 0;
}
